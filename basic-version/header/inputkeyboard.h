/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#ifndef _KEYBOARDINPUT_H
#define _KEYBOARDINPUT_H

#include <stdbool.h>
/*
   Details in ../docs/keyboardInput.md
*/
#define CTRL_KEY(key) ((key) & 0x1f)
typedef enum {
    TAB = 9,       
    ENTER = 10,     
    ESC = '\x1b',  
    ARROW_UP = 1000,
    ARROW_DOWN,
    ARROW_RIGHT,
    ARROW_LEFT,
    HOME_KEY,       // ESC[H
    END_KEY,        // ESC[F
    DELETE_KEY,     // ESC[3~
    INSERT_KEY,     // ESC[2~
    PAGE_UP,        // ESC[5~
    PAGE_DOWN,      // ESC[6~
} ControlKey;

/*
    Processing Key input from readKeyPress;
*/
void processingKeypress();
int readKeypress();
/*
    Arrow key up = [ + 'A' -> 2 byte
    '\x1b' is ESC
*/
int readMoveKey();
int convertArrowOrHomeEndKeyToMoveValue(char key);
int convertPageMoveOrDeteleInsertKeyToMoveValue(char *key) ;
/*
    Processing keyword to move cursor by arrows
*/
void moveCursorByArrows(int arrow);
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
bool stillInRowsContainContent();
void cursorAtOutOfLine();

/***    Test functions      ***/
void printInputFromKeyboard(char c);

#endif