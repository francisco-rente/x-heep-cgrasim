// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef HW_CGRAITF_DPI_H_
#define HW_CGRAITF_DPI_H_

#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BUF_SIZE 1
#define SV_SOCKET_PATH "/tmp/cgrasim"

struct cgraitfdpi_ctx
{
    int sock;
};


void *cgraitfdpi_create();
int cgraitfdpi_read(void *ctx_void);
void cgraitfdpi_close(void *ctx_void);
void cgraitfdpi_write(void *ctx_void, int data);

#ifdef __cplusplus
}
#endif
#endif  // CGRAITF_DPI_H_
