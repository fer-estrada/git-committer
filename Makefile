CC = cc
CFLAGS = -Wall -g 

all: main
dev: clean main

./build/git_commands.o: ./src/git_commands.c ./src/git_commands.h
	$(CC) -c ./src/git_commands.c -o ./build/git_commands.o

./build/main.o: ./build/git_commands.o
	$(CC) -c ./src/main.c -o ./build/main.o

main: ./build/main.o ./build/git_commands.o
	$(CC) ./build/main.o ./build/git_commands.o -o git_commit

clean:
	rm -rf ./build/* ./git_commit

.PHONY: all dev clean
