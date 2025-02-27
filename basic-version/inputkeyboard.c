/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#include "inputkeyboard.h"
#include "errorhandle.h"
#include "outputscreen.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int convertArrowOrHomeEndKeyToMoveValue(char key) {
    switch (key)
    {
        case 'A': return ARROW_UP;
        case 'B': return ARROW_DOWN;
        case 'C': return ARROW_RIGHT;
        case 'D': return ARROW_LEFT;
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;
    }
    return ESC;
}
#define BYTE_READ_INPUT sizeof(char)
int convertPageMoveOrDeteleInsertKeyToMoveValue(char *key) {
    if(key[1] == '~')
        switch(key[0]){
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '3': return DELETE_KEY;
            case '2': return INSERT_KEY;
        }
    return ESC;
}
int readMoveKey() {
    char seq[3];
    if(read(STDIN_FILENO, &seq[0], BYTE_READ_INPUT) != BYTE_READ_INPUT) return ESC;
    if(read(STDIN_FILENO, &seq[1], BYTE_READ_INPUT) != BYTE_READ_INPUT) return ESC;
    if(seq[0] == '[') {
        if(seq[1] >= '0' && seq[1] <= '9') {
            if(read(STDIN_FILENO, &seq[2], BYTE_READ_INPUT) != BYTE_READ_INPUT) 
                return ESC;
            return convertPageMoveOrDeteleInsertKeyToMoveValue(&*(seq+1)); // take s[1] and s[2]
        }
        return convertArrowOrHomeEndKeyToMoveValue(seq[1]);
    }    
    return ESC;
}
int readKeypress() {
    char c;
    int nread;
    while((nread = read(STDIN_FILENO, &c, BYTE_READ_INPUT)) != BYTE_READ_INPUT) 
        if(nread == READ_INTPUT_FAILED && errno == EAGAIN)
            die("read");
    if(c == ESC) 
        return readMoveKey();
    return (int)c;
}
void processingKeypress() {
    int input = readKeypress();
    switch(input) {
        case CTRL_KEY('q'):
            eraseEntireScreen();
            exit(0);
            break;
        case PAGE_UP:
//             movePage(moveUp);
            config.cursorPosition.cy = 0;
            break;
        case PAGE_DOWN:
//             movePage(moveDown);
            config.cursorPosition.cy = config.erow.numrows;
            break;
        case HOME_KEY:
//             moveToEdgesOfScreen(moveLeft);
            config.cursorPosition.cx = 0;
            break;
        case END_KEY:
//             moveToEdgesOfScreen(moveRight);
            config.cursorPosition.cx = config.erow.row[config.cursorPosition.cy].size - 1;
            break;
        case DELETE_KEY:
            break;
        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_RIGHT:
        case ARROW_LEFT:
            moveCursorByArrows(input);
            break;
    }
}
inline void cursorAtOutOfLine() {
    if(config.cursorPosition.cx > config.erow.row[config.cursorPosition.cy].size)
        config.cursorPosition.cx = config.erow.row[config.cursorPosition.cy].size;
}
inline void moveUp() {
    if(config.cursorPosition.cy > 0) {
        config.cursorPosition.cy--;
        cursorAtOutOfLine();
    }
}
inline void moveDown() {
    if(config.cursorPosition.cy < config.erow.numrows) {
        config.cursorPosition.cy++;
        cursorAtOutOfLine();
    }
}
inline void moveLeft() {
    if(config.cursorPosition.cx > 0)
        config.cursorPosition.cx--;
}
inline void moveRight() {
    if(config.cursorPosition.cx < config.erow.row[config.cursorPosition.cy].size)
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