# Codes 
- `\x1b[2J` sends an ANSI escape command to clear the screen.
- `\x1b[H` Moves the cursor to the top of the screen.
- `\x1b[K` Erase in line
- `\x1b[J` Clears from the cursor position to the bottom of the screen.
- `\x1b[1J` Clears from the top of the screen to the cursor position.
- `\x1b[2J\x1b[H` Clears the entire screen and moves the cursor to the top corner.
# Detail
- `J` command to clear the screen, 
- `2` argument which says to clear entire screen, 
    + <esc>[1] would clear the screen up to where the cursor is
        -> like `\x1b[1J`
    + <esc>[0] would clear the screen from the cursor up to the end of the screen 
        -> like `\x1b[J`
        
- `\x1b[y;xH` -> y and x are the positions where we want the cursor at
# Byte out terminal
- first byte is `\x1b` = ESC to send control signal to terminal, 
other three bytes are `[2J` to erase entire screen 
    + `[` = 1 byte
    + `2` = 1 byte
    + `J` = 1 byte
- `\x1b[2J` -> 4 byte
- `\x1b[H` -> 3 byte
- `\x1b[J` -> 3 byte
- `\x1b[1J` -> 3 byte
- `\x1b[2J\x1b[H` -> 7 byte