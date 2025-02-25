# run:
# 	g++ -g *.cpp -o test_run -lncurses

all: editor
editor: main.c 
	$(CC) -o exe/main *.c -Wall -W -pedantic -std=c99 -I./header -D_GNU_SOURCE
clean:
	exe/main
