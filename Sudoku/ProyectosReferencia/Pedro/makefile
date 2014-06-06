SHELL = /bin/sh
CC = g++
CORE = minisat/core
UTILS = minisat/utils
FLAGS = -Wno-write-strings -Wno-parentheses -I minisat -I $(CORE) $ -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS -O3 -g -D NDEBUG -c
COMPFLAGS = -Wall -lz --static
CODIGOS = $(CORE)/Main.cc $(CORE)/Solver.cc $(UTILS)/Options.cc $(UTILS)/System.cc 
OBJECTS = $(CORE)/Main.o $(CORE)/Solver.o $(UTILS)/Options.o $(UTILS)/System.o 

all: sudoku mainsat

mainsat: $(OBJECTS)
	@g++ $^ $(COMPFLAGS) -o mainsat

%.o: %.cc
	@$(CC) $(FLAGS) $< -o $@

sudoku: sudoku.o $(OBJECTS)
	$(CC) -Wall sudoku.o -o sudoku

sudoku.o: sudoku.cc
	$(CC) -Wall -c sudoku.cc

clean:
	@echo Eliminado
	@rm -f $(OBJECTS)
	@rm -f Proyecto3.o
	@rm -f sudoku
	@echo OK

build: sudoku mainsat