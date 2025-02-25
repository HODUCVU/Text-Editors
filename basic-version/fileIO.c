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
void closeFile(FILE **fp) {
    fclose(*fp);
}
void readContentToRow(char* line, ssize_t lineLen) {
    config.erow.row.size = lineLen;
    config.erow.row.chars = malloc(lineLen + 1);
    memcpy(config.erow.row.chars, line, lineLen);
    config.erow.row.chars[lineLen] = '\0';
    config.erow.numrows += 1;
}
bool removeEndLine(char* line, ssize_t lineLen) {
    return lineLen >= 0 && (line[lineLen - 1] == '\r' || line[lineLen - 1] == '\n');
}
void openEditor(char *filename) {
    FILE *fp = readFile(filename);
    char* line = NULL;
    size_t lineCap = 0;
    ssize_t lineLen = 0;
    // while(fgets(line, lineCap, fp)){
        lineLen = getline(&line, &lineCap, fp);
        if(lineLen != -1) {
            while(removeEndLine(line, lineLen))
                lineLen--;
            readContentToRow(line, lineLen);
        }
    // } 
    free(line);
    closeFile(&fp);
}