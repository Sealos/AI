DEP = node.o search.o
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

all: $(DEP)
	$(CC) $(LIBS) main.cpp $(DEP) $(DFLAGS) $(CPPFLAGS) -o main

%.o: %.cpp
	$(CC) $(LIBS) -c $(DFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f *.o

rebuild: clean all

debug: $(DEP)
	$(CC) $(LIBS) main.cpp $(DEP) $(DFLAGS) $(LIBS) $(CPPFLAGS) -o main

