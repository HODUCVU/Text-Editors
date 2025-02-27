/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#ifndef _ERRORHANDLE_H
#define _ERRORHANDLE_H
#include <errno.h>

/*
    Details at ../docs/errorcodes.md
    Die function that handle error and exit program
    exit(1) to notify program that is an error
*/
void die(const char* s);
#endif