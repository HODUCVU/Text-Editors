# Set Flags to setup terminal 
`lib: <termios.h>`
## Turn off echoing in terminal. 
> ECHO -> set ECHO bit = 0 in c_lflag
- When input some character from keyboard, it won't show on terminal, but after press Enter, it will show on terminal
- We can use this function to make input password from user is invisable

## Turn off canonical mode
> ICANON
- When in canonical mode, user enters entire line before processing.
- When turn canonical mode off, this means we will finally be reading input byte-by-byte, instead of line-by-line.
- That mean, if in canonical mode, program only get user input when user press enter, but when turn off it, program can get any character from user input without press enter

## Disable Ctrl_C and Ctrl_Z 
> make them like normal input
- Turn off ctrl_C and ctrl_Z and ctrl_D signals
> ISIG -> Enable signals.
- When set ISIG is 0 in c_lflag, then ctrl_C and ctrl_Z and ctrl_D (not use) don't cause to exit progam immediately

## Disable Ctrl_S and Ctrl_Q
> Turn to XOFF flow control for Ctrl_S and Ctrl_Q by ~IXON
- Set to `c_iflag` (view on docs/termion.md) 
- `IXO` on is `XON/XOFF` flow control `Ctrl+Q/Ctrl+S`
- `~IXON` that `Ctrl+Q/Ctrl+S` no longer works, enter as normal character

## Diable Ctrl_V
- Set to `c_lflag`.
> IEXTEN enable implementation-defined input processing like `ctrl_V`, `ctrl_O`
- `~IEXTEN` giving the program more control over the input, `ctrlV/ctrl_O` no longer works, enter as normal character.
    
## Fix Ctrl_M and Ctrl_J
- `Ctrl_M` is equal 10, `Ctrl_J` and Enter are both also equal 10.
- Target to set `Ctrl_M` = 13.
- Set to `c_iflag`.
> `ICRNL` -> Map `CR` to `NL` on input. `CR` is carriage return and `NL` is new line.
- Turn off `ICRNL` that make `Ctrl_M` = 13 and `Enter` is also equal 13, but `Ctrl_J` = 10.

## Turn off all output processing
> Set to `c_oflag` with `~OPOST`
- A newline `'\n'` = 10 translated to `'\r\n'`
- So, if want to make a new line, take `'\r\n'`

> Turn off Breaking input like `ctrl_c` by set to `c_iflag = ~BRKINT` (I know, we have done it, but I think we need to make sure that program follow what we want)
> Turn off parity check by set to `c_iflag = ~INPCK`
> Preserve all 8 bits of the character by set to `c_iflag = ~ISTRIP`

> Set to control mode `c_cflag |= CS8` -> set size of data is 8 bit

## Currently, read() will wait indefinitely for input from the keyboard before it returns. 
What if we want to do something like animate something on the screen while waiting for user input? 
We can set a timeout, so that read() returns if it doesn’t get any input for a certain amount of time.
> Set `VMIN` and `VTIME` to `c_cc[type]` to control special event
> `VMIN = 0` -> No need to enter any characters first to start reading
> `VTIME = 1` -> 1 milisecond to exit read() when no characters are entered
> `VERASE` Thay đổi phím xóa 
                               
## Set atext(func) to call disableRawMode when exit program