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

| Cờ	    |            Mô tả                          |             If Disable
|---------|-------------------------------------------|------------------------------------------
| IGNBRK	| Bỏ qua tín hiệu break                     | Ký tự break được xử lý bình thường
| BRKINT	| Tạo tín hiệu SIGINT khi nhận break        | Break được xử lý như ký tự thông thường
| IGNPAR	| Bỏ qua lỗi parity                         | Ký tự có lỗi parity có thể bị thay thế hoặc đánh dấu
| INPCK	  | Bật kiểm tra parity                       | Không kiểm tra lỗi parity
| ISTRIP	| Xóa bit cao nhất (chỉ giữ 7 bit thấp)     | Giữ nguyên tất cả 8 bit của ký tự
| IXON	  | Bật XON/XOFF flow control `Ctrl+Q/Ctrl+S` | `Ctrl+Q/Ctrl+S` no longer works, enter as normal character
| ICRNL   | Ký tự xuống dòng (`\r`) sẽ được ánh xạ thành dòng mới (`\n`)        | `\r` được giữ nguyên
| INLCR   | Ký tự dòng mới (`\n`) sẽ được ánh xạ thành ký tự xuống dòng (`\r`)  | Ký tự `\n` được giữ nguyên
| IGNCR   | Bỏ qua ký tự xuống dòng (`\r`)            | Ký tự `\r` được xử lý bình thường.

2. **tcflag_t c_oflag**; (Output Mode Flags - Cờ chế độ đầu ra)\
Cờ này kiểm soát định dạng đầu ra của terminal, tức là cách terminal xử lý dữ liệu khi in ra màn hình.

| Cờ	    |                Mô tả
|---------|-------------------------------------
| OPOST	  | Bật chế độ xử lý đầu ra (mặc định bật)
| ONLCR	  | Chuyển `\n` thành `\r\n` (xuống dòng + về đầu dòng)
| OCRNL	  | Chuyển `\r` thành `\n`
| ONOCR	  | Không in `\r` khi cột hiện tại là 0
| ONLRET	| Không in `\r` (chỉ xuống dòng)

3. **tcflag_t c_cflag**; (Control Mode Flags - Cờ chế độ điều khiển)\
Cờ này kiểm soát các thuộc tính truyền thông như số bit dữ liệu, bit chẵn lẻ, tốc độ baud, số bit stop.

| Cờ	               |           Mô tả
|--------------------|---------------------------
| CS5, CS6, CS7, CS8 | Số bit dữ liệu (thường là CS8)
| CSTOPB	           | 2-bit stop (mặc định là 1-bit)
| PARENB	           | Bật kiểm tra parity
| PARODD	           | Dùng parity lẻ (nếu không có, mặc định là chẵn)
| CRTSCTS	           | Bật RTS/CTS hardware flow control

4. **tcflag_t c_lflag**; (Local Mode Flags - Cờ chế độ nội bộ)\
Cờ này kiểm soát chế độ hoạt động của terminal, ví dụ chế độ nhập thô (raw mode) hoặc chế độ dòng (canonical mode).

| Cờ	    |                               Mô tả                                     |           If Disable
|---------|-------------------------------------------------------------------------|-------------------------------------------
| ICANON	|       Line mode (user enters entire line before processing)             | Receive byte to byte instead of line to line
| ECHO	  |                   Display input on screen                               | Does not show what the user is typing until Enter is pressed
| ECHOE	  |                 Show delete (Backspace active)                          |
| ECHOK	  |                 Show `Ctrl+U` (delete entire line)                      |
| ISIG	  |     Allow signals like `Ctrl+C` (SIGINT) and `Ctrl+Z` (SIGTSTP)         | ctrl_C and ctrl_Z and ctrl_D (not use) don't cause to exit progam immediately
| IEXTEN	| Enable implementation-defined input processing like `ctrl_V`, `ctrl_O`  | Giving the program more control over the input, `ctrlV/ctrl_O` no longer works, enter as normal character

5. **cc_t c_line**; (Line Discipline - Kỷ luật dòng)\
Dùng để chỉ định cách terminal xử lý dòng lệnh.\
Thường có giá trị 0 (default).

6. **cc_t c_cc\[NCCS\]**; (Control Characters - Các ký tự điều khiển)\
Mảng này lưu trữ các ký tự điều khiển đặc biệt của terminal, chẳng hạn như Ctrl+C, Ctrl+D, Ctrl+Z.

| Macro    | Mô tả                                          | Phím mặc định  |
|----------|------------------------------------------------|----------------|
| VINTR    | Ngắt tiến trình (gửi `SIGINT`)                 | `Ctrl+C`       |
| VQUIT    | Thoát và tạo core dump (`SIGQUIT`)             | `Ctrl+\`       |
| VERASE   | Xóa một ký tự                                  | `Backspace`    |
| VKILL    | Xóa toàn bộ dòng hiện tại                      | `Ctrl+U`       |
| VEOF     | Kết thúc nhập (`EOF`)                          | `Ctrl+D`       |
| VTIME    | Thời gian chờ (milliseconds) khi đọc dữ liệu   | *Không có phím*|
| VMIN     | Số ký tự tối thiểu cần nhập trước khi đọc      | *Không có phím*|
| VSWTC    | Không sử dụng trên Linux (switch character)    | *Không có phím*|
| VSTART   | Tiếp tục đầu ra (`XON`, bật lại output)        | `Ctrl+Q`       |
| VSTOP    | Dừng đầu ra (`XOFF`, tạm dừng output)          | `Ctrl+S`       |
| VSUSP    | Tạm dừng tiến trình (`SIGTSTP`)                | `Ctrl+Z`       |
| VEOL     | Ký tự kết thúc dòng (`end-of-line`)            | *Không có phím*|
| VREPRINT | In lại dòng bị xóa (`reprint line`)            | `Ctrl+R`       |
| VDISCARD | Bật/tắt chế độ bỏ qua đầu vào                  | `Ctrl+O`       |
| VWERASE  | Xóa một từ phía trước con trỏ                  | `Ctrl+W`       |
| VLNEXT   | Nhập ký tự đặc biệt mà không xử lý             | `Ctrl+V`       |
| VEOL2    | Ký tự kết thúc dòng thứ hai (`alternate EOL`)  | *Không có phím*|

7. **speed_t c_ispeed**; và speed_t c_ospeed;\
`c_ispeed`: Tốc độ truyền đầu vào (input baud rate).\
`c_ospeed`: Tốc độ truyền đầu ra (output baud rate).\

|Macro    |	Tốc độ (bps)
|---------|-------------|
|B0	      |	Không truyền
|B50	    |	50 bps
|B9600	  |	9600 bps (mặc định)
|B115200	|	115200 bps (cao hơn)
