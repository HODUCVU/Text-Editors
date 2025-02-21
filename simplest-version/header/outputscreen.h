#ifndef _OUTPUTSCREEN_H
#define _OUTPUTSCREEN_H

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
/*
    Daw a column of tildes (~) like in vim.
    In the future, I will replace this to number column
*/
void drawRows();
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
int getWindowSize(int *row, int *col);

#endif