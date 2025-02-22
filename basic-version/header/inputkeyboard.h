#ifndef _KEYBOARDINPUT_H
#define _KEYBOARDINPUT_H

/*
    Keyboard shortcut values
    using iscntrl(char) in <ctype.h> to get ctrl key shortcut

    Or just
--> #define CTRL_KEY(key) ((key) & 0x1f)
    to define ctrl keyword, like CTRL_Q == CTRL_KEY('q')
*/
typedef enum {
    TAB = 9,        // Move to another file while ESC
    ENTER = 10,     // Enter edit mode while ESC
    ESC = 27,       // Exit edit mode
    CTRL_A = 1,     // select all
    CTRL_Q = 17,    // quit
    CTRL_S = 19,    // save
    CTRL_U = 21,    // redo
    CTRL_V = 22,    // past
    CTRL_C = 3,     // copy
    CTRL_X = 24,    // cut
    CTRL_Y = 25,    // undo
    CTRL_Z = 26,    // undo, can use CTRL_Y instead.
    LEFT_ARROW = 37,
    UP_ARROW = 38,
    RIGHT_ARROW = 39,
    DOWN_ARROW = 40,
} ControlKey;

/*
    lib: <unistd.h>
--> - Read keyboard input to buffer by read().
    - Keyboard input is only sent to your program when the user presses Enter.

    - enableRawMode() to config input from keyboard to terminal, 
        like exit by ctr+Q, save by ctr+S, copy by ctr+C, past by ctr+V, cut by ctr+X, etc...
    - Using iscntrl(char) in <ctype.h> to get ctrl key
    
    - Configuration termios control flags to do something if no input in 1 milisecond 
    - c_cc[VMIN] = 0 -> No need to enter any characters first to start reading
    - c_cc[VTIME] = 1 -> 1 milisecond to exit read() when no characters are entered

    Check until read is success -> read = 1 (sizeof(char)), but if read = -1 then kill program
*/
char readKeypress();
/*
    Processing Key input from readKeyPress;
*/
void processingKeypress();

/***    Test functions      ***/
void printInputFromKeyboard(char c);

#endif