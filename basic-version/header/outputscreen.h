/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#ifndef _OUTPUTSCREEN_H
#define _OUTPUTSCREEN_H

#include "global.h"
#include <stdbool.h>

/*
    Design a buffer to minimun use write() function -> prevent hiding bugs
    using <string.h> to copy current buffer to new buffer when want to append new character
*/
typedef struct Abuffer {
    char *b;
    int len;
} Abuffer;
void appendBuffer(Abuffer *buffer, const char* s, int len);
void freeBuffer(Abuffer *buffer);
/*
    lib: <unistd.h>
    Fuctions used: write() to write on terminal output
    This function use to erase screen
    write 4 byte to terminal

    cursor: https://vt100.net/docs/vt100-ug/chapter3.html#CUP
*/

void eraseEntireScreen();
/*
    Refresh screen, but still write something on editor
*/
void refreshScreen();
void writeOutScreen(Abuffer *buffer);

/*
    Daw a column of tildes (~) like in vim.
    In the future, I will replace this to number column
    
    '~' is tilde to draw row
    '\r\n' is enter a new line, 
    I transform \n to \r\n to get a new line in settingterminal.h
    output like this:
    ~
    ~
    ~
    ...

    "\x1b[K": Erase in line
    + 2 erases the whole line
    + 1 erases the part of the line to the left of the cursor
    + 0 erases the part of the line to the right of the cursor
*/
void drawRow(Abuffer *buffer, int row);
// void drawRefershScreenToBuffer(Abuffer *buffer);
void drawTitleEditor(Abuffer *buffer);
int writeContentToRows(Abuffer *buffer) ;
void drawEditorScreen(Abuffer *buffer);

void moveCursorToCurrentPosition(Abuffer *buffer);
/*
    Build window size of editor
    lib: <sys/ioctl.h>
    Call ioctl() with TIOCGWINSZ to get window size from struct winsize
    return x == cols and y == row;
--> But to make sure to be able to request the window size on all terminal,
        use Cursor move:
            + 'C': move forward
            + 'B': move down
            + 'D': move Backward
            + 'A': move up
    Make upper limit equal 999, which ensure that the cursor reached the right
            and bottom edges of the screen
        That are "\x1b[999C" and "\x1b[999B"

--? But when we change the size of screen, 
        it will not update size of editor, how fix this?
*/
int getWindowSize(WindowXY *window);

/*
    Get cursor position
    Use "\x1b[6n" with:
        + "n": query the terminal for status information
        + "6": to ask for the cursor position
    -> result: 
        + 27: ESC === \x1b
        + [
        + y
        + x
        + R
        Like this: \x1b[45;66R
        -> x = 66 and y = 45, that is end of screen position
    Read into a buffer until 'R'
    -> buffer = '\x1b[y;x'
    -> buffer[1] = '[y;x'

    Check:
        printf("\r\n");
        char c;
        while(read(STDIN_FILENO, &c, 1) == 1) {
            if(iscntrl(c)) 
                printf("%d\r\n", c);
            else 
                printf("%d ('%c')\r\n", c, c);
        }
*/

bool askCursorPosition();
void readCursorInfoIntoBuffer(char *buffer, int bufferSize);
int parsePositionFromBuffer(char *buffer, WindowXY *window);
int getCurserPosition(WindowXY *window);

void welcomeMessage(Abuffer *buffer);

#endif