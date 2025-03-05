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

FILE* readFile(char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp) die("fopen");
    return fp;
}
inline void closeFile(FILE **fp) {
    fclose(*fp);
}

inline bool removeEndLine(char* line, ssize_t lineLen) {
    return lineLen > 0 && (line[lineLen - 1] == '\r' || line[lineLen - 1] == '\n');
}

void appendRow(char* line, size_t lineLen) {
    config.configErow.erow = realloc(config.configErow.erow, sizeof(Erow)*(config.configErow.numrows + 1));
    int at = config.configErow.numrows;

    config.configErow.erow[at].size = lineLen;
    config.configErow.erow[at].chars = malloc(lineLen + 1);
    memcpy(config.configErow.erow[at].chars, line, lineLen);
    config.configErow.erow[at].chars[lineLen] = '\0';

    config.configErow.erow[at].render = NULL;
    config.configErow.erow[at].renderSize = 0;
    updateRowForRender(&config.configErow.erow[at]);

    config.configErow.numrows++;
}

// Just copy Erow.chars and convert '\t' to 8 white spaces to fix render tab
#define TAB_TO_WHITE_SPACE 8
void updateRowForRender(Erow *row) {
    int tabs = 0;
    int idxOfRender = 0;

    for(int idxOfChars = 0; idxOfChars < row->size; idxOfChars++) 
        if(row->chars[idxOfChars] == '\t') 
            tabs++;
    
    free(row->render);
    row->render = malloc(row->size + tabs*(TAB_TO_WHITE_SPACE - 1) + 1);

    for(int idxOfChars = 0; idxOfChars < row->size; idxOfChars++) {
        if(row->chars[idxOfChars] == '\t') {
            row->render[idxOfRender++] = ' ';
            while(idxOfRender % TAB_TO_WHITE_SPACE != 0) row->render[idxOfRender++] = ' ';
        } else
            row->render[idxOfRender++] = row->chars[idxOfChars];
    }
    row->render[idxOfRender] = '\0';
    row->renderSize = idxOfRender;
}
