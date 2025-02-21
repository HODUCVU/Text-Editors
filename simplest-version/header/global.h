#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <termios.h>

/***        Define attributes       ***/

typedef struct WindowXY {
    int screenRows;
    int screenCols;
} WindowXY;
struct Config {
    /*
        Store rows and cols of entire screen
    */
    WindowXY windowXY;
    /*
        To return original terminal setting for user when program exit 
        or just don't need to visable input from keyboard.
    */
    struct termios original_termios;
};

/***    Global variables/functions    ***/
extern struct Config config;

#endif