#include "keypress.h"
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

// void enableRawMode() {
//     struct termios raw;
//     tcgetattr(STDIN_FILENO, &raw);
//     raw.c_lflag = raw.c_lflag & ~(ECHO);
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
// }
void setRawMode(int enable) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag = enable ? raw.c_lflag | ECHO : raw.c_lflag & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); 
}

void readKeyPress() {
    setRawMode(0);
    char c;
    while(read(STDIN_FILENO, &c, 1) == 1 && c != CTRL_Q ) {
        testInput(c);
    }
}
void testInput(char c) {
    if(c == ' ') printf("\n");
    else printf("%c", c);
}