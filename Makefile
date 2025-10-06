CC = cc
FLAGS = -Wall 

all: main

./build/git_commands.o: ./src/git_commands.c ./src/git_commands.h
	$(CC) -c ./src/git_commands.c -o ./build/git_commands.o $(FLAGS)

./build/main.o: ./build/git_commands.o
	$(CC) -c ./src/main.c -o ./build/main.o $(FLAGS)

main: ./build/main.o ./build/git_commands.o
	$(CC) ./build/main.o ./build/git_commands.o -o git_commit $(FLAGS)
