
#include "cgraitfdpi.h"

#ifdef __linux__
#include <pty.h>
#elif __APPLE__
#include <util.h>
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/time.h>



void *cgraitfdpi_create(){
    // will block until the sock is opened for reading
    // Assumes that the sock is re-created every time
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx * )malloc(sizeof(struct cgraitfdpi_ctx));
    

    int sfd, cfd;
    struct sockaddr_un *addr = (struct sockaddr_un *)malloc(sizeof(struct sockaddr_un));

    // Create a socket with Unix domain
    printf("Creating socket\n");
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sfd == -1){
        perror("socket");
        exit(1);
    }
 
    if(remove(SV_SOCKET_PATH) == -1 && errno != ENOENT){
        perror("remove");
        exit(1);
    }


    // set timeout in socket
    struct timeval tv;  
    tv.tv_sec = 10; 
    tv.tv_usec = 0;
    setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv); 

    printf("Creating address\n");
    memset(addr, 0, sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    strncpy(addr->sun_path, SV_SOCKET_PATH, sizeof(addr->sun_path) - 1);

    printf("Binding to %s\n", SV_SOCKET_PATH);
    if(bind(sfd, (struct sockaddr *)addr, sizeof(struct sockaddr_un)) == -1){
        perror("bind");
        exit(1);
    }

    printf("Listening on %s\n", SV_SOCKET_PATH);
    if(listen(sfd, 1) == -1){
        perror("listen");
        exit(1);
    }

    printf("Accepting connection\n");

    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(sfd, &rfds);
    int statsus = select(sfd + 1, &rfds, (fd_set *)0, (fd_set *)0, &tv);
    
    if (statsus == -1) {
        perror("select");
        exit(1);
    } else if (statsus == 0) {
        printf("Timeout\n");
        exit(1);
    }
    

    cfd = accept(sfd, NULL, NULL);
    if(cfd == -1){
        perror("accept");
        exit(1);
    }

    ctx->sock = cfd;
    printf("Connected\n");
    return ctx;

}


int cgraitfdpi_read(void *ctx_void){
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx *)ctx_void;
    int data;
    printf("Reading\n");
    // TODO: add error handling, maybe timeout ??
    int ret = recv(ctx->sock, &data, sizeof(data), MSG_WAITALL);
    
    if (ret == -1){
        perror("recv");
        cgraitfdpi_close(ctx_void);
        exit(1);
    }

    printf("Read %d\n", data);
    return data;
}


void cgraitfdpi_close(void *ctx_void){
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx *)ctx_void;
    close(ctx->sock);
    free(ctx);
}

void cgraitfdpi_write(void *ctx_void, int data){
    printf("Writing %d\n", data);
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx *)ctx_void;

    unsigned char buf[4];
    buf[0] = (data >> 24) & 0xFF;
    buf[1] = (data >> 16) & 0xFF;
    buf[2] = (data >> 8) & 0xFF;
    buf[3] = data & 0xFF;

    int ret = send(ctx->sock, &buf, sizeof(buf), 0);
    if (ret == -1){
        perror("send");
        cgraitfdpi_close(ctx_void);
        exit(1);
    }
}
