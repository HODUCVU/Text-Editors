#include "initialize.h"
#include "global.h"
#include "outputscreen.h"
#include "errorhandle.h"
#include <stdlib.h>

#define START_X_CURSOR 0
#define START_Y_CURSOR 2
#define START_NUMBER_OF_ROWS 0
void initWindowSize() {
    config.cursorPosition.cx = START_X_CURSOR;
    config.cursorPosition.cy = START_Y_CURSOR;
    config.scrolling.rowoffset = START_Y_CURSOR;
    config.erow.numrows = START_NUMBER_OF_ROWS;
    config.erow.row = NULL;
    if((getWindowSize(&config.windowXY)) == SETTING_WINDOW_ERROR)
        die("getWindowSize");
}