/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#include "initialize.h"
#include "global.h"
#include "outputscreen.h"
#include "errorhandle.h"
#include <stdlib.h>

#define START_X_CURSOR 0
#define START_Y_CURSOR 0
#define START_NUMBER_OF_ROWS 0

void initEditor() {
    initPosition();
    initScrolling();
    initRowsContent();

    if((getWindowSize(&config.windowXY)) == SETTING_WINDOW_ERROR)
        die("getWindowSize");
}

void initPosition() {
    config.cursorPosition.cx = START_X_CURSOR;
    config.cursorPosition.rx = START_X_CURSOR;
    config.cursorPosition.cy = START_Y_CURSOR;
}

void initScrolling() {
    config.scrolling.coloffset = START_X_CURSOR;
    config.scrolling.rowoffset = START_Y_CURSOR;
}

void initRowsContent() {
    config.configErow.erow = NULL;
    config.configErow.numrows = START_NUMBER_OF_ROWS;
}