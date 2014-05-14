DEP = funciones.o utils.o othello_cut.o

all: $(DEP)
	g++ -std=c++11 main.cc $(DEP) -g -O3 -O2 -Wall -o main

%.o: %.cpp
	g++ -std=c++11 -c -g -O3 -O2 -Wall $<

clean:
	rm -f *.o main

rebuild: clean all
