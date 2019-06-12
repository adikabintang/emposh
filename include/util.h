#ifndef _UTIL_H
#define _UTIL_H

#define EMPOSH_TOKEN_BUFSIZE 64

#define CHECK_MALLOC_RETURN(pointer)                    \
    if (!pointer) {                                     \
        fprintf(stderr, "emposh: allocation error\n");  \
        exit(EXIT_FAILURE);                             \
    }

void emposh_loop();

#endif