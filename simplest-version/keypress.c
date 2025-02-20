/***    includes    ***/
#include "keypress.h"
#include "errorhandle.h"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <ctype.h>

/***    Global variables/functions and extern variables/functions   ***/
extern void die(const char* s);
// To return original terminal setting for user when program exit or just don't need to visable input from keyboard.
struct termios original_termios;

/***    Define functions --> Config Terminal    ***/
void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
        die("tcsetattr");
}
void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &original_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = setFlagsForRawMode(original_termios);
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}
struct termios setFlagsForRawMode(struct termios raw) {
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    return raw;
}
void readKeyPress() {
    enableRawMode();
    while(1) {
        char c = '\0';
        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) // errno from <errno.h> in "errorhandle.h"
            die("read");
        if((int)c == CTRL_Q)
            break;
        testInput(c);
    }
}

/***    Test functions  ***/
void testInput(char c) {
    if(iscntrl(c))
        printf("%d\r\n",c);
    else
        printf("%d ('%c')\r\n",c,c);
}