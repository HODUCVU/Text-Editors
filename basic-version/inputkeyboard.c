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

void eraseEntireScreen(); // from outputscreen.h

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
        case PAGE_UP:
            config.cursorPosition.cy = 0;
            cursorAtOutOfLine();
            break;
        case PAGE_DOWN:
            config.cursorPosition.cy = config.configErow.numrows-1;
            cursorAtOutOfLine();
            break;
        case HOME_KEY:
            config.cursorPosition.cx = 0;
            break;
        case END_KEY:
            config.cursorPosition.cx = config.configErow.erow[config.cursorPosition.cy].renderSize - 1;
            break;
    }
}
#define BYTE_READ_INPUT sizeof(char)
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
inline void moveUp() {
    if(config.cursorPosition.cy > 0) {
        config.cursorPosition.cy--;
        cursorAtOutOfLine();
    }
}
inline void moveDown() {
    if(stillInRowsContainContent()) {
        config.cursorPosition.cy++;
        cursorAtOutOfLine();
    }
}
void moveLeft() {
    if(config.cursorPosition.cx > 0) {
        config.cursorPosition.cx--;
    }
    else if(config.cursorPosition.cy > 0){
        config.cursorPosition.cy--;
        config.cursorPosition.cx = config.configErow.erow[config.cursorPosition.cy].renderSize;
    }
}
void moveRight() {
    if(stillInRowsContainContent()) {
        if (config.cursorPosition.cx < config.configErow.erow[config.cursorPosition.cy].renderSize){
            config.cursorPosition.cx++;
        }
        else {
            config.cursorPosition.cy++;
            config.cursorPosition.cx = 0;
        }
    }
}
inline bool stillInRowsContainContent() {
    return config.cursorPosition.cy < config.configErow.numrows;
}
void cursorAtOutOfLine() {
    if(config.cursorPosition.cx > config.configErow.erow[config.cursorPosition.cy].renderSize)
        config.cursorPosition.cx = config.configErow.erow[config.cursorPosition.cy].renderSize;
    if(!stillInRowsContainContent())   
        config.cursorPosition.cx = 0;
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