#include "errorhandle.h"
#include "outputscreen.h"
#include <stdio.h>
#include <stdlib.h>

void die(const char *s) {
    eraseEntireScreen();
    perror(s);
    exit(1);
}