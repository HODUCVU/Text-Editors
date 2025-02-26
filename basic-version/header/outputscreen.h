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
/*
    "\x1b[2J" sends an ANSI escape command to clear the screen.
    "\x1b[H": Moves the cursor to the top of the screen.
    "\x1b[K": Erase in line
    "\x1b[J": Clears from the cursor position to the bottom of the screen.
    "\x1b[1J": Clears from the top of the screen to the cursor position.
    "\x1b[2J\x1b[H": Clears the entire screen and moves the cursor to the top corner.

    + "J" command to clear the screen, 
    + "2" argument which says to clear entire screen, 
        <esc>[1] would clear the screen up to where the cursor is
            -> like "\x1b[1J"
        <esc>[0] would clear the screen from the cursor up to the end of the screen 
            -> like "\x1b[J"
            
    "\x1b[y;xH" -> y and x are the positions where we want the cursor at

    first byte is "\x1b" = ESC to send control signal to terminal, 
    other three bytes are [2J to erase entire screen 
        + "["" = 1 byte
        + "2" = 1 byte
        + "J" = 1 byte
    "\x1b[2J" -> 4 byte
    "\x1b[H" -> 3 byte
    "\x1b[J" -> 3 byte
    "\x1b[1J" -> 3 byte
    "\x1b[2J\x1b[H" -> 7 byte
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
void newLine(Abuffer *buffer, int row);
void drawRow(Abuffer *buffer, char* content, int sizeContent);
int drawTitleEditor(Abuffer *buffer);
// bool isFileLargerThanVerticalScreen();
void writeContentToRows(Abuffer *buffer, int row) ;
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

void verticalScroll();

#endif


// inline bool isFileLargerThanVerticalScreen() {
//     return config.erow.numrows > config.windowXY.screenRows;
// }
// int numberOfDigitsOfRow(int r) {
//     int temp = r;
//     int rsize = (r == 0) ? 1 : 0; // Handle case where r == 0
//     while (temp > 0) {
//         temp /= 10;
//         rsize++;
//     }
//     return rsize;
// }
// char* convertNumberToChars(int r, int *rsize) {
//     *rsize = numberOfDigitsOfRow(r);
//     char* str = malloc(*rsize + 1); 
//     if (str) {
//         sprintf(str, "%d", r);
//     }
//     return str;
// }
// void drawRowNumber(Abuffer *buffer, int row) {
//     int rsize = 0;
//     char* rowNumber = convertNumberToChars(row, &rsize);
//     drawRow(buffer, rowNumber, rsize+1);
//     drawRow(buffer, " ", 1);
//     free(rowNumber);
// }