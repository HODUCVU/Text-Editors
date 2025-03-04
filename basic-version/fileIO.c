/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE
#include "fileIO.h"
#include "global.h"
#include "errorhandle.h"
#include <stdlib.h>
#include <string.h>

FILE* readFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) die("fopen");
    return fp;
}
inline void closeFile(FILE **fp) {
    fclose(*fp);
}
void appendRow(char* line, size_t lineLen) {
    config.erow.row = realloc(config.erow.row, sizeof(Erow)*(config.erow.numrows + 1));
    int at = config.erow.numrows;
    config.erow.row[at].size = lineLen;
    config.erow.row[at].chars = malloc(lineLen + 1);
    memcpy(config.erow.row[at].chars, line, lineLen);
    config.erow.row[at].chars[lineLen] = '\0';
    config.erow.row[at].render = NULL;
    config.erow.row[at].renderSize = 0;
    config.erow.numrows++;
}
inline bool removeEndLine(char* line, ssize_t lineLen) {
    return lineLen > 0 && (line[lineLen - 1] == '\r' || line[lineLen - 1] == '\n');
}
void openEditor(char *filename) {
    FILE *fp = readFile(filename);
    char* line = NULL;
    size_t lineCap = 0;
    ssize_t lineLen = 0;
    while((lineLen = getline(&line, &lineCap, fp)) != -1){
        while(removeEndLine(line, lineLen))
            lineLen--;
        appendRow(line, lineLen);
    } 
    free(line);
    closeFile(&fp);
}