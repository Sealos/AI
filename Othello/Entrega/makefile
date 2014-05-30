DEP = othello_cut.h funciones.o

all: $(DEP)
	g++ -std=c++11 main.cc $(DEP) -g -O3 -O2 -o main

%.o: %.cpp
	g++ -std=c++11 -c -g -O3 -O2 -w $<

clean:
	rm -f *.o main main.exe

rebuild: clean all
