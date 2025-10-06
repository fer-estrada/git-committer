CC = cc
CFLAGS = -Wall -g 
BIN = /usr/local/bin

all: git_commit
dev: clean git_commit
reinstall: all install

./build/git_commands.o: ./src/git_commands.c ./src/git_commands.h
	$(CC) -c ./src/git_commands.c -o ./build/git_commands.o

./build/main.o: ./build/git_commands.o
	$(CC) -c ./src/main.c -o ./build/main.o

git_commit: ./build/main.o ./build/git_commands.o
	$(CC) ./build/main.o ./build/git_commands.o -o git_commit

run:
	./git_commit

install: git_commit
	install -m 755 git_commit $(BIN)/git_commit

clean:
	rm -rf ./build/* ./git_commit

.PHONY: all dev clean run install reinstall
