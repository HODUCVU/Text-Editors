#include "outputscreen.h"
#include "global.h"
#include "inputkeyboard.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERASE_ENTIR_ESCREEN "\x1b[2J\x1b[H"
/*
    "\x1b[2J" sends an ANSI escape command to clear the screen.
    "\x1b[H": Moves the cursor to the top of the screen.
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

#define DRAW_ROW_SYMBOL "~\r\n"
#define START_CURSOR "\x1b[H"
#define BYTE_OUT_DRAW_ROW 3
/*
    '~' is tilde to draw row
    '\r\n' is enter a new line, 
    I transform \n to \r\n to get a new line in settingterminal.h
    output like this:
    ~
    ~
    ~
    ...
*/
void drawRows() {
    int row = 0;
    for(; row < config.windowXY.screenRows; row++) {
        write(STDOUT_FILENO, DRAW_ROW_SYMBOL, BYTE_OUT_DRAW_ROW);
    }
    write(STDOUT_FILENO, START_CURSOR, BYTE_OUT_DRAW_ROW);
}
void refreshScreen() {
    eraseEntireScreen();
    drawRows();
}


#define BOTTOM_RIGHT_CURSOR "\x1b[999C\x1b[999B"
#define BYTE_OUT_BOTTOM_RIGHT_CURSOR 12 // 6 + 6
#define ASK_CURRENT_CURSOR_POSITION "\x1b[6n"
#define BYTE_OUT_ASK_CURSOR_POSITION 4
#define BUFFER_SIZE 32
bool askCursorPosition() {
    return write(STDOUT_FILENO, ASK_CURRENT_CURSOR_POSITION, BYTE_OUT_ASK_CURSOR_POSITION)
    != BYTE_OUT_ASK_CURSOR_POSITION;
}
void readIntoBuffer(char *buffer, int bufferSize) {
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
int getCurserPosition() {
    char buffer[BUFFER_SIZE];
    if(askCursorPosition()) return -1;
    readIntoBuffer(buffer, BUFFER_SIZE);
    printf("\r\n&buffer[1]: '%s' \r\n", &buffer[1]);
    readKeypress();
    return -1;
}

int getWindowSize(int *row, int *col){
    struct winsize wsize;
    if(1 || ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize) == -1 || wsize.ws_col == 0) {
        if(write(STDOUT_FILENO, BOTTOM_RIGHT_CURSOR, BYTE_OUT_BOTTOM_RIGHT_CURSOR)
            != BYTE_OUT_BOTTOM_RIGHT_CURSOR)
            return -1;
        return getCurserPosition();
    }
    *col = wsize.ws_col;
    *row = wsize.ws_row;
    return 0;
}