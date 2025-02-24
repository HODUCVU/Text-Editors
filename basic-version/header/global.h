#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <termios.h>

/***        Define attributes       ***/
/*
    cx and cy are tracking position of current cursor
*/
typedef struct CursorPosition {
    int cx, cy;
} CursorPostiion;
/*
    Store rows and cols of entire screen
    screenRows and screenCols are position at the end of terminal
*/
typedef struct WindowXY {
    int screenRows;
    int screenCols;
} WindowXY;
struct Config {
    CursorPostiion cursorPosition;
    WindowXY windowXY;
    /*
        To return original terminal setting for user when program exit 
        or just don't need to visable input from keyboard.
    */
    struct termios original_termios;
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