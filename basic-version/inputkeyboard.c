#include "inputkeyboard.h"
#include "errorhandle.h"
#include "outputscreen.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define BYTE_READ_INPUT sizeof(char)
#define READ_INTPUT_FAIL -1
char readKeypress() {
    char c;
    int nread;
    while((nread = read(STDIN_FILENO, &c, BYTE_READ_INPUT)) != BYTE_READ_INPUT) 
        if(nread == READ_INTPUT_FAIL && errno == EAGAIN)
            die("read");
    return c;
}
void processingKeypress() {
    int input = readKeypress();
    switch(input) {
        case CTRL_Q:
            eraseEntireScreen();
            exit(0);
            break;
    }
    // printInputFromKeyboard((char)input);
}

/***    Test functions  ***/
void printInputFromKeyboard(char c) {
    if(c == '\0')
        return;
    if(iscntrl(c))
        printf("%d\r\n",c);
    else
        printf("%d ('%c')\r\n",c,c);
}