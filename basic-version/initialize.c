#include "initialize.h"
#include "global.h"
#include "outputscreen.h"
#include "errorhandle.h"
#include <stdlib.h>

void initWindowSize() {
    if((getWindowSize(&config.windowXY)) == -1)
        die("getWindowSize");
}