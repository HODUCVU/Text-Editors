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

/*
   Details in ../docs/keyboardInput.md
*/
#define CTRL_KEY(key) ((key) & 0x1f)
typedef enum {
    TAB = 9,        // Move to another file while ESC
    ENTER = 10,     // Enter edit mode while ESC
    ESC = '\x1b',   // Exit edit mode
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

int readKeypress();
/*
    Arrow key up = [ + 'A' -> 2 byte, and plus 1 byt '\0'
    '\x1b' is ESC
*/
int readMoveKey();
/*
    Processing Key input from readKeyPress;
*/
void processingKeypress();
/*
    Processing keyword to move cursor by arrows
*/
// void moveCursorByHJKL(char key); -> set ESC state to us hjkl move cursor
void moveCursorByArrows(int arrow);
int convertArrowOrHomeEndKeyToMoveValue(char key);
int convertPageMoveOrDeteleInsertKeyToMoveValue(char *key) ;
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void cursorAtOutOfLine();
// void movePage(void(*callback)());
// void moveToEdgesOfScreen(void(*callback)());

/***    Test functions      ***/
void printInputFromKeyboard(char c);

#endif