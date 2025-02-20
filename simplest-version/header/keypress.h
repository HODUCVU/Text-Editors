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
    Turn off echoing in terminal.
    When input some character from keyboard, it won't show on terminal, 
        but after press Enter, it will show on terminal
*/
// void enableRawMode();
/*
    Turn on/off echoing in terminal
    just set bit ECHO in c_lflag
    We can use this function to make input password from user is invisable
    Usage:
        Set 0 to disable echoing
        Set 1 to enable echoing
*/
void setRawMode(int enable);
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