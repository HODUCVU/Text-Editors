/***    includes    ***/
#include "settingterminal.h"
#include "errorhandle.h"
#include "global.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

/***   Extern variables/functions   ***/
extern void die(const char* s);

/***    Define functions --> Config Terminal    ***/
void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &config.original_termios) == -1)
        die("tcsetattr");
}
void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &config.original_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = setFlagsForRawMode(config.original_termios);
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