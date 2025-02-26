/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#include "errorhandle.h"
#include "outputscreen.h"
#include <stdio.h>
#include <stdlib.h>

void die(const char *s) {
    eraseEntireScreen();
    perror(s);
    exit(1);
}