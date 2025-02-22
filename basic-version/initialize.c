#include "initialize.h"
#include "global.h"
#include "outputscreen.h"
#include "errorhandle.h"
#include <stdlib.h>


#define SETTING_WINDOW_ERROR -1

void initWindowSize() {
    if((getWindowSize(&config.windowXY)) == SETTING_WINDOW_ERROR)
        die("getWindowSize");
}