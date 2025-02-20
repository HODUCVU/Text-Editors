```
struct termios
  {
    tcflag_t c_iflag;		/* input mode flags */
    tcflag_t c_oflag;		/* output mode flags */
    tcflag_t c_cflag;		/* control mode flags */
    tcflag_t c_lflag;		/* local mode flags */
    cc_t c_line;			/* line discipline */
    cc_t c_cc[NCCS];		/* control characters */
    speed_t c_ispeed;		/* input speed */
    speed_t c_ospeed;		/* output speed */
  #define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
  #define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
  };
```
 1.**tcflag_t c_iflag**; (Input Mode Flags - Cờ chế độ đầu vào)\
Cờ này điều khiển cách terminal xử lý đầu vào (input), chẳng hạn như cách xử lý ký tự xóa (Backspace), chuyển đổi ký tự (CR -> LF), v.v.

| Cờ	    |            Mô tả                          | If Disable
|---------|-------------------------------------------|-----------
| IGNBRK	| Bỏ qua tín hiệu break                     |
| BRKINT	| Tạo tín hiệu SIGINT khi nhận break        |
| IGNPAR	| Bỏ qua lỗi parity                         |
| INPCK	  | Bật kiểm tra parity                       |
| ISTRIP	| Xóa bit cao nhất (chỉ giữ 7 bit thấp)     |
| IXON	  | Bật XON/XOFF flow control `Ctrl+Q/Ctrl+S` | `Ctrl+Q/Ctrl+S` no longer works, enter as normal character
| ICRNL   |     |
2. **tcflag_t c_oflag**; (Output Mode Flags - Cờ chế độ đầu ra)\
Cờ này kiểm soát định dạng đầu ra của terminal, tức là cách terminal xử lý dữ liệu khi in ra màn hình.

| Cờ	    |                Mô tả
|---------|-------------------------------------|
| OPOST	  | Bật chế độ xử lý đầu ra (mặc định bật)
| ONLCR	  | Chuyển \n thành \r\n (xuống dòng + về đầu dòng)
| OCRNL	  | Chuyển \r thành \n
| ONOCR	  | Không in \r khi cột hiện tại là 0
| ONLRET	| Không in \r (chỉ xuống dòng)

3. **tcflag_t c_cflag**; (Control Mode Flags - Cờ chế độ điều khiển)\
Cờ này kiểm soát các thuộc tính truyền thông như số bit dữ liệu, bit chẵn lẻ, tốc độ baud, số bit stop.

| Cờ	               |           Mô tả
|--------------------|---------------------------|
| CS5, CS6, CS7, CS8 | Số bit dữ liệu (thường là CS8)
| CSTOPB	           | 2-bit stop (mặc định là 1-bit)
| PARENB	           | Bật kiểm tra parity
| PARODD	           | Dùng parity lẻ (nếu không có, mặc định là chẵn)
| CRTSCTS	           | Bật RTS/CTS hardware flow control
4. **tcflag_t c_lflag**; (Local Mode Flags - Cờ chế độ nội bộ)\
Cờ này kiểm soát chế độ hoạt động của terminal, ví dụ chế độ nhập thô (raw mode) hoặc chế độ dòng (canonical mode).

| Cờ	    |                               Mô tả                                 |       If Disable
|---------|---------------------------------------------------------------------|-------------------------------------------
| ICANON	|       Line mode (user enters entire line before processing)         | Receive byte to byte instead of line to line
| ECHO	  |                   Display input on screen                           | Does not show what the user is typing until Enter is pressed
| ECHOE	  |                 Show delete (Backspace active)                      |
| ECHOK	  |                 Show Ctrl+U (delete entire line)                    |
| ISIG	  |     Allow signals like Ctrl+C (SIGINT) and Ctrl+Z (SIGTSTP)         | ctrl_C and ctrl_Z and ctrl_D (not use) don't cause to exit progam immediately
| IEXTEN	| Enable implementation-defined input processing like ctrl_V, ctrl_O  | Giving the program more control over the input, ctrlV/ctrl_O no longer works, enter as normal character

5. **cc_t c_line**; (Line Discipline - Kỷ luật dòng)\
Dùng để chỉ định cách terminal xử lý dòng lệnh.\
Thường có giá trị 0 (default).

6. **cc_t c_cc\[NCCS\]**; (Control Characters - Các ký tự điều khiển)\
Mảng này lưu trữ các ký tự điều khiển đặc biệt của terminal, chẳng hạn như Ctrl+C, Ctrl+D, Ctrl+Z.

| Chỉ mục	|         Mô tả	                | Mặc định
|---------|-------------------------------|--
| VINTR	  | Ctrl+C  (ngắt chương trình)	  | \003
| VQUIT	  | *Ctrl+*  (thoát chương trình) | \034
| VERASE	| Backspace (xóa ký tự)	        | \177
| VKILL	  | Ctrl+U (xóa dòng)	            |\025
| VEOF	  | Ctrl+D (kết thúc nhập)	      |\004
| VSUSP	  | Ctrl+Z (tạm dừng)	            |\032

7. **speed_t c_ispeed**; và speed_t c_ospeed;\
c_ispeed: Tốc độ truyền đầu vào (input baud rate).\
c_ospeed: Tốc độ truyền đầu ra (output baud rate).\

|Macro    |	Tốc độ (bps)
|---------|-------------|
|B0	      |	Không truyền
|B50	    |	50 bps
|B9600	  |	9600 bps (mặc định)
|B115200	|	115200 bps (cao hơn)
