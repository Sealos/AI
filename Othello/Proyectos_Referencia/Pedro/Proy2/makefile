CC=g++
all: main

main: main.o
	$(CC) -Wall main.o -o main
main.o: main.cc othello_cut.h
	$(CC) -Wall -c main.cc othello_cut.h

build: main