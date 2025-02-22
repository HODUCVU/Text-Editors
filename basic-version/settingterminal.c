/***    includes    ***/
#include "settingterminal.h"
#include "errorhandle.h"
#include "global.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

/***   Extern variables/functions   ***/
void die(const char* s);

/***    Define functions --> Config Terminal    ***/
#define SETTING_TERMINAL_ERROR -1
void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &config.original_termios) == SETTING_TERMINAL_ERROR)
        die("tcsetattr");
}
void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &config.original_termios) == SETTING_TERMINAL_ERROR)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = setFlagsForRawMode(config.original_termios);
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == SETTING_TERMINAL_ERROR)
        die("tcsetattr");
}

#define START_READING_AFTER_NUMBER_OF_CHARS 0
#define MINIMUN_MILISECOND_TIMEOUT 1
struct termios setFlagsForRawMode(struct termios raw) {
    raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN); 
    raw.c_cflag |= (CS8);
    raw.c_cc[VMIN] = START_READING_AFTER_NUMBER_OF_CHARS;
    raw.c_cc[VTIME] = MINIMUN_MILISECOND_TIMEOUT;
    return raw;
}