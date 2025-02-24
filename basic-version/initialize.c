#include "initialize.h"
#include "global.h"
#include "outputscreen.h"
#include "errorhandle.h"
#include <stdlib.h>

#define START_X_CURSOR 0
#define START_Y_CURSOR 2
void initWindowSize() {
    config.cursorPosition.cx = START_X_CURSOR;
    config.cursorPosition.cy = START_Y_CURSOR;
    if((getWindowSize(&config.windowXY)) == SETTING_WINDOW_ERROR)
        die("getWindowSize");
}