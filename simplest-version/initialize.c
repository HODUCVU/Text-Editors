#include "initialize.h"
#include "global.h"
#include "outputscreen.h"
#include "errorhandle.h"
#include <stdlib.h>

void initWindowSize() {
    if((getWindowSize(&config.windowXY.screenRows, &config.windowXY.screenCols)) == -1)
        die("getWindowSize");
}