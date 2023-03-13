#pragma once

#include <string.h>

#define BUF_SIZE        512
#define FMT_BUF_SIZE    512

extern char buffer[BUF_SIZE];
extern unsigned bp;
extern char format_buffer[FMT_BUF_SIZE];

// append string literal to buffer
#define append(buf, bufptr, str)     memcpy(&buf[bufptr], str, sizeof(str) - 1);\
                                     (bufptr += sizeof(str) - 1)

// append string to buffer
#define append_str(buf, bufptr, str) (register size_t len = strlen(str));\
                                     memcpy(&buf[bufptr], str, strlen(str));\
                                     (bufptr += len)

// append char to buffer
#define append_char(buf, bufptr, ch) (buf[bufptr++] = ch)
