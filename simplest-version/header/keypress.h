#ifndef _KEYPRESS_H
#define _KEYPRESS_H

typedef enum {
    CTRL_A = 1,
    CTRL_Q = 17,
    CTRL_S = 19,
    UP_ARROW,
    DOWN_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW

} ControlKey;
/*
    lib: <termios.h>
    Turn off echoing in terminal. -> set ECHO bit = 0 in c_lflag
    When input some character from keyboard, it won't show on terminal, 
        but after press Enter, it will show on terminal
    We can use this function to make input password from user is invisable

    Turn off canonical mode
*/
void enableRawMode();
/*
    When we enableRawMode, set **atexit()** to disableRawMode, that function register disableRawMode to be called when `exit' is called.
    include <stdlib.h> for atexit()
    
    Turn off echoing in terminal -> just set ECHO bit = 1 in c_lflag
    When exit program or don't need to invisable what character user input
    
    Turn on canonical mode
*/
void disableRawMode();
/*
    lib: <unistd.h>
    Read keyboard input to buffer.
    Keyboard input is only sent to your program when the user presses Enter.
*/
void readKeyPress();
/*
    Test functions
*/
void testInput(char c);
#endif