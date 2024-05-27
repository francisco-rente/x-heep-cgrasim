
#include "cgraitfdpi.h"

#ifdef __linux__
#include <pty.h>
#elif __APPLE__
#include <util.h>
#endif


#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>


void *cgraitfdpi_create(){
    // will block until the file is opened for reading
    // Assumes that the file is re-created every time
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx *)malloc(sizeof(struct cgraitfdpi_ctx));
    
    int rv;

    rv = mkfifo("/tmp/cgrasim", 0666);

    if (rv != 0){
        perror("mkfifo");
    }

    assert(rv == 0);

    ctx->file = fopen("/tmp/cgrasim", "w");

    // Nothing is buffered in the file
    rv = setvbuf(ctx->file, NULL, _IONBF, 0);
    assert(rv == 0);

    return ctx;

}
void cgraitfdpi_close(void *ctx_void){
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx *)ctx_void;
    fclose(ctx->file);
    free(ctx);
}
void cgraitfdpi_write(void *ctx_void, int data){
    struct cgraitfdpi_ctx *ctx = (struct cgraitfdpi_ctx *)ctx_void;
    fprintf(ctx->file, "%d\n", data);
    fflush(ctx->file);
}