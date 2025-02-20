#ifndef _KEYPRESS_H
#define _KEYPRESS_H

/*
    Keyboard shortcut values
    using iscntrl(char) in <ctype.h> to get ctrl key shortcut
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
    For more details, read at docs/termios.md

    lib: <termios.h>
    Turn off echoing in terminal. 
    #define ECHO 0000010 -> set ECHO bit = 0 in c_lflag
    - When input some character from keyboard, it won't show on terminal, 
        but after press Enter, it will show on terminal
    - We can use this function to make input password from user is invisable

    Turn off canonical mode
    #define ICANON 0000002
    - When in canonical mode, user enters entire line before processing.
    - When turn canonical mode off, this means we will finally be reading input byte-by-byte, instead of line-by-line.
    - That mean, if in canonical mode, program only get user input when user press enter, 
        but when turn off it, program can get any character from user input without press enter

    Disable Ctrl_C and Ctrl_Z -> make them like normal input
    Turn off ctrl_C and ctrl_Z and ctrl_D signals
    #define ISIG 0000001 -> Enable signals.
    - When set ISIG is 0 in c_lflag, then ctrl_C and ctrl_Z and ctrl_D (not use) don't cause to exit progam immediately

    Disable Ctrl_S and Ctrl_Q
    Turn to XOFF flow control for Ctrl_S and Ctrl_Q by ~IXON
    - Set to c_iflag (view on docs/termion.md) 
    - IXO on is XON/XOFF flow control `Ctrl+Q/Ctrl+S`
    - ~IXON that `Ctrl+Q/Ctrl+S` no longer works, enter as normal character

    Diable Ctrl_V
    - Set to c_lflag
    - IEXTEN enable implementation-defined input processing like ctrl_V, ctrl_O 
    - ~IEXTEN giving the program more control over the input, ctrlV/ctrl_O no longer works, enter as normal character
    
    Set atext(func) to call disableRawMode when exit program
*/
void enableRawMode();
/*
    lib: include <stdlib.h> for atexit(func)
    When we enableRawMode, set **atexit(func)** to disableRawMode, 
        that function register disableRawMode to be called when `exit' is called.
    
    Setting terminal return to original setting
    Turn off echoing in terminal -> just set ECHO bit = 1 in c_lflag
    Turn on cannonical mode
    When exit program or don't need to invisable what character user input
*/
void disableRawMode();
/*
    lib: <unistd.h>
    - Read keyboard input to buffer.
    - Keyboard input is only sent to your program when the user presses Enter.

    - enableRawMode() to config input from keyboard to terminal, 
        like exit by ctr+Q, save by ctr+S, copy by ctr+C, past by ctr+V, cut by ctr+X, etc...
    - Using iscntrl(char) in <ctype.h> to get ctrl key
*/
void readKeyPress();
/*
    Test functions
*/
void testInput(char c);
#endif