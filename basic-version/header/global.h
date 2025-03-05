/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <termios.h>

/***        Define attributes       ***/
/*
    cx and cy are tracking position of current cursor
    rx used to move in horizontal navigation for tab
*/
typedef struct CursorPosition {
    int cx, cy;
    int rx;
} CursorPostiion;

/*
    Store rows and cols of entire screen
    screenRows and screenCols are position at the end of terminal
*/
typedef struct WindowXY {
    int screenRows;
    int screenCols;
} WindowXY;

/*
    Data type for storing a row of text in editor
*/
typedef struct Erow {
    char *chars; // for content
    char *render; // for tab
    int size;
    int renderSize;
} Erow;
typedef struct ConfigERows {
    Erow *erow;
    int numrows;
} ConfigERows;

typedef struct Scrolling{
    int rowoffset; // for vertical scrolling
    int coloffset; // for horizontal scrolling
} Scrolling;

struct Config {
    struct termios original_termios;
    ConfigERows configErow;
    CursorPostiion cursorPosition;
    WindowXY windowXY;
    Scrolling scrolling;
};

typedef enum {
    READ_TERMINAL_SIZE_FAILED = -1,
    SETTING_TERMINAL_ERROR = -1,
    SETTING_WINDOW_ERROR = -1,
    READ_INTPUT_FAILED = -1
} ERRORVALUES;

typedef enum {
    SETTING_WINDOW_SUCCESS,
} SUCCESSVALUES;

/***    Global variables/functions    ***/
extern struct Config config;

#endif