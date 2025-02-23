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
void freeBuffer(Abuffer *buffer) {
    free(buffer->b);
}

#define ERASE_ENTIR_ESCREEN "\x1b[2J\x1b[H"
/*
    "\x1b[2J" sends an ANSI escape command to clear the screen.
    "\x1b[H": Moves the cursor to the top of the screen.
    "\x1b[K": Erase in line
    "\x1b[J": Clears from the cursor position to the bottom of the screen.
    "\x1b[1J": Clears from the top of the screen to the cursor position.
    "\x1b[2J\x1b[H": Clears the entire screen and moves the cursor to the top corner.

    + "J" command to clear the screen, 
    + "2" argument which says to clear entire screen, 
        <esc>[1] would clear the screen up to where the cursor is
            -> like "\x1b[1J"
        <esc>[0] would clear the screen from the cursor up to the end of the screen 
            -> like "\x1b[J"
            
    "\x1b[y;xH" -> y and x are the positions where we want the cursor at
*/
#define BYTE_OUT_TO_TERMINAL 7
/* 
    first byte is "\x1b" = ESC to send control signal to terminal, 
    other three bytes are [2J to erase entire screen 
        + "["" = 1 byte
        + "2" = 1 byte
        + "J" = 1 byte
    "\x1b[2J" -> 4 byte
    "\x1b[H" -> 3 byte
    "\x1b[J" -> 3 byte
    "\x1b[1J" -> 3 byte
    "\x1b[2J\x1b[H" -> 7 byte
*/
void eraseEntireScreen() {
    write(STDOUT_FILENO, ERASE_ENTIR_ESCREEN, BYTE_OUT_TO_TERMINAL);
}

#define VERSION_EDITOR "0.0.1"
#define BUFFER_SIZE 32
#define NEW_LINE "\r\n"
void welcomeMessage(Abuffer *buffer) {
    char welcome[BUFFER_SIZE];
    int welcomeLen = snprintf(welcome, sizeof(welcome),
            "BASIC VERSION -- version %s", VERSION_EDITOR);
    if(welcomeLen > config.windowXY.screenCols)
        welcomeLen = config.windowXY.screenCols;
    int padding = (config.windowXY.screenCols - welcomeLen)/2;
    for(int col = 0; col < padding; col++)
        appendBuffer(buffer, " ", 1);
    appendBuffer(buffer, welcome, welcomeLen);
    appendBuffer(buffer, NEW_LINE, 2);
}

#define DRAW_ROW_SYMBOL "~"
#define BYTE_OUT_DRAW_ROW 1
#define ERASE_RIGHT_EACH_LINE_FROM_CURSOR "\x1b[K"
#define BYTE_OUT_CLEAR_EACH_LINE 3
#define ERASE_TOP_SCREEN "\x1b[1J\x1b[H"
void drawRefershScreenToBuffer(Abuffer *buffer) {
    appendBuffer(buffer, ERASE_TOP_SCREEN, BYTE_OUT_TO_TERMINAL);
    welcomeMessage(buffer);
    for(int row = 1; row < config.windowXY.screenRows; row++) {
        appendBuffer(buffer, DRAW_ROW_SYMBOL, BYTE_OUT_DRAW_ROW);
        appendBuffer(buffer, ERASE_RIGHT_EACH_LINE_FROM_CURSOR, BYTE_OUT_CLEAR_EACH_LINE);
        if(row < config.windowXY.screenRows - 1)
            appendBuffer(buffer, NEW_LINE, 2);
    }
}

// #define START_POSITION_OF_CURSOR "\x1b[2;0H"
// #define BYTE_OUT_START_POSITION_OF_CURSOR 6
#define START_POSITION_OF_CURSOR "\x1b[H"
#define BYTE_OUT_START_POSITION_OF_CURSOR 3
void moveCursonToTopOfScreen(Abuffer *buffer) {
    appendBuffer(buffer, START_POSITION_OF_CURSOR, BYTE_OUT_START_POSITION_OF_CURSOR);
}
/*
    range [1 -> n]
    init y = 2; x = 0 -> y = 2; x = x + 1 = 1
    because begin position in terminal is 1;1
*/
#define PARSE_POSITION_OF_CURSOR "\x1b[%d;%dH"
void moveCursorToCurrentPosition(Abuffer *buffer) {
    char temp_buff[BUFFER_SIZE];
    snprintf(temp_buff, BUFFER_SIZE, PARSE_POSITION_OF_CURSOR, 
        config.cursorPosition.cy, config.cursorPosition.cx + 1);
    appendBuffer(buffer, temp_buff, strlen(temp_buff));
}
void writeOutScreen(Abuffer *buffer) {
    write(STDOUT_FILENO, buffer->b, buffer->len);
}

#define HIDE_CURSOR "\x1b[?25l"
#define SHOW_CURSOR "\x1b[?25h"
#define BYTE_OUT_DISPLAY_STATUS_CURSOR 6
void refreshScreen() {
    Abuffer buffer = ABUFFER_INIT;
    appendBuffer(&buffer, HIDE_CURSOR, BYTE_OUT_DISPLAY_STATUS_CURSOR);
    drawRefershScreenToBuffer(&buffer);
    moveCursorToCurrentPosition(&buffer);
    appendBuffer(&buffer, SHOW_CURSOR, BYTE_OUT_DISPLAY_STATUS_CURSOR);
    writeOutScreen(&buffer);
    freeBuffer(&buffer);
}

#define BOTTOM_RIGHT_CURSOR "\x1b[999C\x1b[999B"
#define BYTE_OUT_BOTTOM_RIGHT_CURSOR 12 // 6 + 6
#define ASK_CURRENT_CURSOR_POSITION "\x1b[6n"
#define BYTE_OUT_ASK_CURSOR_POSITION 4
#define SETTING_WINDOW_ERROR -1
#define SETTING_WINDOW_SUCCESS 0
bool askCursorPosition() {
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
int parsePositionFromBuffer(char *buffer, WindowXY *window) {
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

#define READ_TERMINAL_SIZE_FAILED -1
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