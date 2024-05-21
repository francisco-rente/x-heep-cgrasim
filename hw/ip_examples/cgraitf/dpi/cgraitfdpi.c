
#include "cgraitfdpi.h"

#ifdef __linux__
#include <pty.h>
#elif __APPLE__
#include <util.h>
#endif

/*#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>*/
#include <stdio.h>
/*#include <stdlib.h>
#include <string.h>
#include <unistd.h>*/
#include <sys/stat.h>

void testCGRASim_itf(int data) {

  // get the fifo file from the CGRASIM_PIPE environment variable
  // char *fifo_path = getenv("CGRASIM_PIPE");
  // if (fifo_path == NULL) {
  //   fprintf(stderr, "CGRASIM_PIPE environment variable not set\n");
  //   return;
  // }


  mkfifo("/tmp/cgrasim", 0666);

  FILE *fifo = fopen("/tmp/cgrasim", "w");
  if (fifo == NULL) {
    fprintf(stderr, "Failed to open fifo\n");
    return;
  }

  fprintf(fifo, "%d\n", data);
  fclose(fifo);
}
