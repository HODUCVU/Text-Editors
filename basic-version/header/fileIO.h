#ifndef _FILEIO_H
#define _FILEIO_H

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
FILE* readFile(char *filename);
void closeFile(FILE **fp) ;
bool removeEndLine(char* line, ssize_t lineLen);
void appendRow(char* line, size_t lineLen);
/*
    ssize_t from <sys/types.h> 
    malloc from <stdlib.h>
*/
void openEditor(char *filename);

#endif