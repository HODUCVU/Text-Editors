/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#ifndef _KEYPRESS_H
#define _KEYPRESS_H

/***    Initialization functions --> Config Terminal *  **/
/*
    For more details, read at ../docs/termios.md and ../docs/settingTerminal
*/
struct termios setFlagsForRawMode(struct termios raw);
void enableRawMode();
/*
    lib: include <stdlib.h> for atexit(func)
    When we enableRawMode, set **atexit(func)** to disableRawMode, 
        that function register disableRawMode to be called when `exit' is called.
    
    Setting terminal return to original setting
    Turn off echoing in terminal -> just set ECHO bit = 1 in c_lflag
    Turn on cannonical mode
    ...
*/
void disableRawMode();

#endif
