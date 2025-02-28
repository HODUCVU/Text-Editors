/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#include "outputscreen.h"
#include "global.h"
#include "inputkeyboard.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ABUFFER_INIT {NULL, 0}
void appendBuffer(Abuffer *buffer, const char* s, int len) {
    char *new_buffer = realloc(buffer->b, buffer->len + len);
    if(new_buffer == NULL)
        return;
    memcpy(&new_buffer[buffer->len], s, len);
    buffer->b = new_buffer;
    buffer->len += len;
}
inline void freeBuffer(Abuffer *buffer) {
    free(buffer->b);
}

#define ERASE_ENTIR_ESCREEN "\x1b[2J\x1b[H"
#define BYTE_OUT_TO_TERMINAL 7 // \x1b[2J = 4 and \x1b[H = 3
inline void eraseEntireScreen() {
    write(STDOUT_FILENO, ERASE_ENTIR_ESCREEN, BYTE_OUT_TO_TERMINAL);
}

#define VERSION_EDITOR "0.0.1"
#define BUFFER_SIZE 32
int setMessageTitle(char *welcome) {
    int welcomeLen =  snprintf(welcome, BUFFER_SIZE,
        "BASIC VERSION -- version %s", VERSION_EDITOR);
        if(welcomeLen > config.windowXY.screenCols)
        welcomeLen = config.windowXY.screenCols;
        return welcomeLen;
    }
#define NEW_LINE "\r\n"
#define BYTE_OUT_NEW_LINE 2
void welcomeMessage(Abuffer *buffer) {
    char welcome[BUFFER_SIZE];
    int welcomeLen = setMessageTitle(welcome);
    int padding = (config.windowXY.screenCols - welcomeLen)/2;
    for(int col = 0; col < padding; col++)
        appendBuffer(buffer, " ", 1);
    appendBuffer(buffer, welcome, welcomeLen);
    appendBuffer(buffer, NEW_LINE, BYTE_OUT_NEW_LINE);
}
#define DRAW_ROW_SYMBOL "~"
#define BYTE_OUT_DRAW_ROW 1
#define ERASE_RIGHT_EACH_LINE_FROM_CURSOR "\x1b[K"
#define BYTE_OUT_CLEAR_EACH_LINE 3
#define ERASE_TOP_SCREEN "\x1b[1J\x1b[H"
int drawTitleEditor(Abuffer *buffer) {
    appendBuffer(buffer, ERASE_TOP_SCREEN, BYTE_OUT_TO_TERMINAL);
    int beginAt = 1;
    if(config.erow.numrows == 0)
        welcomeMessage(buffer);
    else beginAt = 0;
    return beginAt;
}
inline void newLine(Abuffer *buffer, int row) {
    appendBuffer(buffer, ERASE_RIGHT_EACH_LINE_FROM_CURSOR, BYTE_OUT_CLEAR_EACH_LINE);
    if(row < config.windowXY.screenRows-1)
        appendBuffer(buffer, NEW_LINE, BYTE_OUT_NEW_LINE);
}
inline void drawRow(Abuffer *buffer, char* content, int sizeContent) {
    appendBuffer(buffer, content, sizeContent);
}
/*
    source Size                              |----------|
    coloffset                                |----|
    horizontal show = sourceSize - coloffset |------|
    Move with coloffset                      ____|------|
*/
int convertContentWithHorizontalOffset(int sourceSize) {
    sourceSize -= config.scrolling.coloffset;
    return sourceSize >= 0 ? sourceSize : 0;
}
void writeContentToRows(Abuffer *buffer, int row) {
    int sizeChars = config.erow.row[row].size;
    sizeChars = convertContentWithHorizontalOffset(sizeChars);
    if(sizeChars > config.windowXY.screenCols) 
        sizeChars = config.windowXY.screenCols;
    drawRow(buffer, &config.erow.row[row].chars[config.scrolling.coloffset], sizeChars);
}
void drawEditorScreen(Abuffer *buffer) {
    int row = drawTitleEditor(buffer);
    for(; row < config.windowXY.screenRows; row++) {
        int filerow = row + config.scrolling.rowoffset;
        if(filerow >= config.erow.numrows) {
            drawRow(buffer, DRAW_ROW_SYMBOL, BYTE_OUT_DRAW_ROW);
        } else
            writeContentToRows(buffer, filerow);
        newLine(buffer, row);
    }
}
/*
    init y = 0; x = 0 -> plus 1 to both y and x 
    because begin position in terminal is 1;1
*/
#define PARSE_POSITION_OF_CURSOR "\x1b[%d;%dH"
void moveCursorToCurrentPosition(Abuffer *buffer) {
    char temp_buff[BUFFER_SIZE];
    snprintf(temp_buff, BUFFER_SIZE, PARSE_POSITION_OF_CURSOR, 
        (config.cursorPosition.cy - config.scrolling.rowoffset)+1, 
        (config.cursorPosition.cx - config.scrolling.coloffset)+1);
    appendBuffer(buffer, temp_buff, strlen(temp_buff));
}
inline void writeOutScreen(Abuffer *buffer) {
    write(STDOUT_FILENO, buffer->b, buffer->len);
}

#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"
#define BYTE_OUT_DISPLAY_STATUS_CURSOR 6
void refreshScreen() {
    verticalScroll();
    horizontalSroll();
    Abuffer buffer = ABUFFER_INIT;
    appendBuffer(&buffer, HIDE_CURSOR, BYTE_OUT_DISPLAY_STATUS_CURSOR);
    drawEditorScreen(&buffer);
    moveCursorToCurrentPosition(&buffer);
    appendBuffer(&buffer, SHOW_CURSOR, BYTE_OUT_DISPLAY_STATUS_CURSOR);
    writeOutScreen(&buffer);
    freeBuffer(&buffer);
}

#define BOTTOM_RIGHT_CURSOR "\x1b[999C\x1b[999B"
#define BYTE_OUT_BOTTOM_RIGHT_CURSOR 12 // \x1b[999C = 6 and \x1b[999B = 6
#define ASK_CURRENT_CURSOR_POSITION "\x1b[6n"
#define BYTE_OUT_ASK_CURSOR_POSITION 4
inline bool askCursorPosition() {
    return write(STDOUT_FILENO, ASK_CURRENT_CURSOR_POSITION, BYTE_OUT_ASK_CURSOR_POSITION)
    != BYTE_OUT_ASK_CURSOR_POSITION;
}
void readCursorInfoIntoBuffer(char *buffer, int bufferSize) {
    int readIdx = 0;
    while(readIdx < bufferSize - 1) {
        if(read(STDIN_FILENO,&buffer[readIdx], 1) != 1) 
            break;
        if(buffer[readIdx] == 'R')
            break;
        readIdx++;
    }
    buffer[readIdx] = '\0';
}
inline int parsePositionFromBuffer(char *buffer, WindowXY *window) {
    if(buffer[0] != '\x1b' || buffer[1] != '[')
        return SETTING_WINDOW_ERROR;
    return sscanf(&buffer[2], "%d;%d", &(*window).screenRows, &(*window).screenCols);
}
int getCurserPosition(WindowXY *window) {
    char buffer[BUFFER_SIZE];
    if(askCursorPosition()) return SETTING_WINDOW_ERROR;
    readCursorInfoIntoBuffer(buffer, BUFFER_SIZE);
    if(parsePositionFromBuffer(buffer, window) != 2)
        return SETTING_WINDOW_ERROR;
    return SETTING_WINDOW_SUCCESS;
}

int getWindowSize(WindowXY *window){
    struct winsize wsize;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize) == READ_TERMINAL_SIZE_FAILED || wsize.ws_col == 0) {
        if(write(STDOUT_FILENO, BOTTOM_RIGHT_CURSOR, BYTE_OUT_BOTTOM_RIGHT_CURSOR)
            != BYTE_OUT_BOTTOM_RIGHT_CURSOR)
            return SETTING_WINDOW_ERROR;
        return getCurserPosition(window);
    }
    (*window).screenCols = wsize.ws_col;
    (*window).screenRows = wsize.ws_row;
    return SETTING_WINDOW_SUCCESS;
}

void verticalScroll() {
    // scroll up
    if(config.cursorPosition.cy < config.scrolling.rowoffset) 
        config.scrolling.rowoffset = config.cursorPosition.cy;
    // scroll down
    if(config.cursorPosition.cy >= config.scrolling.rowoffset + config.windowXY.screenRows)
        config.scrolling.rowoffset = config.cursorPosition.cy - config.windowXY.screenRows + 1;
}

void horizontalSroll() {
    // Scroll to left
    if(config.cursorPosition.cx < config.scrolling.coloffset)
        config.scrolling.coloffset = config.cursorPosition.cx;
    // Scroll to right
    if(config.cursorPosition.cx >= config.scrolling.coloffset + config.windowXY.screenCols)
        config.scrolling.coloffset = config.cursorPosition.cx - config.windowXY.screenCols + 1;
}