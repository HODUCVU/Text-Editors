#include "inputkeyboard.h"
#include "errorhandle.h"
#include "outputscreen.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


char readKeypress() {
    char c;
    int nread;
    // Check until read is success -> read = 1, but if read = -1 then kill program
    while((nread = read(STDIN_FILENO, &c, 1)) != 1) 
        if(nread == -1 && errno == EAGAIN)
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