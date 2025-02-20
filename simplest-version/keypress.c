#include "keypress.h"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

// To return original terminal setting for user when program exit or just don't need to visable input from keyboard.
struct termios original_termios;
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit(disableRawMode);
    struct termios raw = original_termios;
    raw.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
void readKeyPress() {
    enableRawMode();
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != CTRL_Q ) {
        testInput(c);
    }
}
void testInput(char c) {
    if(c == ' ') printf("\n");
    else printf("%c", c);
}