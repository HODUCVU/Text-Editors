/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
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
void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &config.original_termios) == SETTING_TERMINAL_ERROR)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = setFlagsForRawMode(config.original_termios);
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == SETTING_TERMINAL_ERROR)
        die("tcsetattr");
}

void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &config.original_termios) 
        == SETTING_TERMINAL_ERROR)
        die("tcsetattr");
}

#define INVISABLE_KEY_SHOW ~ECHO
#define READ_BYTE_TO_BYTE ~ICANON
#define DISABLE_CTRL_C_Z ~ISIG
#define DISABLE_CTRL_V ~IEXTEN

#define DISABLA_CTRL_S_O ~IXON
#define FIX_CTRL_M_J ~ICRNL
#define DISABLE_BREAKING_INPUT ~BRKINT
#define DISABLE_PARIRY_CHECK ~INPCK
#define PRESERVE_ALL_8_BITS ~ISTRIP

#define CONVERT_ENDLINE_TO_TABENDLINE ~OPOST
#define SET_DATA_IS_8BITS CS8

#define START_READING_AFTER_NUMBER_OF_CHARS 0
#define MINIMUN_MILISECOND_TIMEOUT 1
struct termios setFlagsForRawMode(struct termios raw) {
    raw.c_lflag &= INVISABLE_KEY_SHOW & READ_BYTE_TO_BYTE & DISABLE_CTRL_C_Z & DISABLE_CTRL_V; 
    raw.c_iflag &= DISABLA_CTRL_S_O & FIX_CTRL_M_J & DISABLE_BREAKING_INPUT & DISABLE_PARIRY_CHECK & PRESERVE_ALL_8_BITS;
    raw.c_oflag &= CONVERT_ENDLINE_TO_TABENDLINE;
    raw.c_cflag |= SET_DATA_IS_8BITS;
    raw.c_cc[VMIN] = START_READING_AFTER_NUMBER_OF_CHARS;
    raw.c_cc[VTIME] = MINIMUN_MILISECOND_TIMEOUT;
    return raw;
}