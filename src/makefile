TARGET = main
CC = g++
DFLAGS = -g
LIBS = -std=c++11

LBITS = $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
	CPPFLAGS = -D X_64 -Wall
else
	CPPFLAGS = -Wall
endif

all: node.o
	$(CC) $(LIBS) main.cpp node.o $(DFLAGS) $(CPPFLAGS) -o main

%.o: %.cpp
	$(CC) -c $(LIBS) $(DFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o

rebuild: clean all

debug: node.o
	$(CC) $(LIBS) main.cpp node.o $(DFLAGS) $(LIBS) $(CPPFLAGS) -o main

