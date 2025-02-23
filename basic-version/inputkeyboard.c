#include "inputkeyboard.h"
#include "errorhandle.h"
#include "outputscreen.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int convertKeyInputToArrowValue(char key) {
    switch (key)
    {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
    }
    return ESC;
}
#define BYTE_READ_INPUT sizeof(char)
int readArrowKey() {
    char seq[3];
    if(read(STDIN_FILENO, &seq[0], BYTE_READ_INPUT) != BYTE_READ_INPUT) return ESC;
    if(read(STDIN_FILENO, &seq[1], BYTE_READ_INPUT) != BYTE_READ_INPUT) return ESC;
    if(seq[0] == '[') return convertKeyInputToArrowValue(seq[1]);
    return ESC;
}
#define READ_INTPUT_FAIL -1
int readKeypress() {
    char c;
    int nread;
    while((nread = read(STDIN_FILENO, &c, BYTE_READ_INPUT)) != BYTE_READ_INPUT) 
        if(nread == READ_INTPUT_FAIL && errno == EAGAIN)
            die("read");
    if(c == ESC) 
        return readArrowKey();
    return (int)c;
}
void processingKeypress() {
    int input = readKeypress();
    switch(input) {
        case CTRL_KEY('q'):
            eraseEntireScreen();
            exit(0);
            break;
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            moveCursorByArrows(input);
            break;
    }
}
void moveUp() {
    if(config.cursorPosition.cy != 2)
        config.cursorPosition.cy--;
}
void moveDown() {
    if(config.cursorPosition.cy != config.windowXY.screenRows - 1)
        config.cursorPosition.cy++;
}
void moveLeft() {
    if(config.cursorPosition.cx == 0) {
        if(config.cursorPosition.cy != 2)
            config.cursorPosition.cx = config.windowXY.screenCols - 1;
        moveUp();
    }
    else config.cursorPosition.cx--;
}
void moveRight() {
    if(config.cursorPosition.cx == config.windowXY.screenCols - 1) {
        config.cursorPosition.cx = 0;
        moveDown();
    } else 
        config.cursorPosition.cx++;
}
void moveCursorByArrows(int arrow) {
    switch(arrow) {
        case ARROW_UP:
            moveUp();
            break;
        case ARROW_DOWN:
            moveDown();
            break;
        case ARROW_RIGHT:
            moveRight();
            break;
        case ARROW_LEFT:
            moveLeft();
            break;
    }
}

/***    Test functions  ***/
void printInputFromKeyboard(char c) {
    if(c == '\0')
        return;
    if(iscntrl(c))
        printf("%d\r\n",c);
    else
        printf("%d ('%c')\r\n",c,c);
}