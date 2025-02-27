# Keyboard shortcut values
## Values
> using iscntrl(char) in `<ctype.h>` to see ctrl key shortcut values
``` 
CTRL_A = 1,     // select all
CTRL_Q = 17,    // quit
CTRL_S = 19,    // save
CTRL_U = 21,    // redo
CTRL_V = 22,    // past
CTRL_C = 3,     // copy
CTRL_X = 24,    // cut
CTRL_Y = 25,    // undo
CTRL_Z = 26,    // undo, can use CTRL_Y instead.
HOME_KEY,       // ESC[H
END_KEY,        // ESC[F
DELETE_KEY,     // ESC[3~
INSERT_KEY,     // ESC[2~
PAGE_UP,        // ESC[5~
PAGE_DOWN,      // ESC[6~
```

## Or just
```#define CTRL_KEY(key) ((key) & 0x1f)```
> To define ctrl keyword, like `CTRL_Q == CTRL_KEY('q')`

# Enable Raw mode in terminal
`lib: "settingterminal.h"`
- Read keyboard input to buffer by `read()`.
- Keyboard input is only sent to your program when the user presses `Enter`.
> `enableRawMode()` to config input from keyboard to terminal, like exit by ctr+Q, save by ctr+S, copy by ctr+C, past by ctr+V, cut by ctr+X, etc...
- Using `iscntrl(char)` in `<ctype.h>` to check ctrl key.
- Configuration termios control flags to do something if no input in 1 milisecond.
- `c_cc[VMIN]` = 0 -> No need to enter any characters first to start reading
- `c_cc[VTIME]` = 1 -> 1 milisecond to exit `read()` when no characters are entered

> Check until read is success -> read = 1 `(sizeof(char))`, but if read = -1 then kill program