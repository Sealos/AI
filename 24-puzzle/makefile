DEP = node.o search.o state.o pdb.o state_ida.o
TARGET = main
CC = g++
DFLAGS = -g -O3 -O2
LIBS = -std=c++11

LBITS = $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	CPPFLAGS = -D X_64 -Wall
else
	CPPFLAGS = -Wall
endif

all: $(DEP)
	$(CC) $(LIBS) main.cpp $(DEP) $(DFLAGS) $(CPPFLAGS) -o main

%.o: %.cpp
	$(CC) $(LIBS) -c $(DFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o main gen_pdb

rebuild: clean all

debug: $(DEP)
	$(CC) $(LIBS) main.cpp $(DEP) $(DFLAGS) $(LIBS) $(CPPFLAGS) -o main

gen:
	g++ -std=c++11 -D X_64 -Wall -g -O3 -O2 -lprofiler gen_pdb.cpp -lprofiler -g -O3 -O2 -o gen_pdb -lprofiler
