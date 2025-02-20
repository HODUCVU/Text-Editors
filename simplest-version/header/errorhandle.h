#ifndef _ERRORHANDLE_H
#define _ERRORHANDLE_H
#include <errno.h>

/*
    Die function that handle error and exit program
    exit(1) to notify program that is an error
    
    perror(s) print error type, from <stdio.h>
    exit() to exit program, from <stdlib.h>

    Using errno from <errno.h> to get error signal for perror.
    Some useful errno:
        ETXTBSY	    Text file busy
        EFBIG       File too large
        EEXIST      File exists
        ENOTDIR		Not a directory
        EISDIR		Is a directory
        EAGAIN      Try again
        ENOMEM		Out of memory
        EPERM       Operation not permitted
        ENOENT      No such file or directory
        EIO		    I/O error
*/
void die(const char* s);
#endif