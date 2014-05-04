#include <stdio.h>
#include <fstream>
#include <sstream>
#include "node.h"
#include "pdb.h"
#include "search.h"


int main(int argc, const char* argv[])
{
	std::ifstream infile(argv[1]);
	std::string line;
	unsigned int representacion[2];
	node *nodo;

	while (std::getline(infile, line))
	{
		representacion[0] = 0x00000000;
		representacion[1] = 0x00000000;
		long unsigned int rep = 0x0000000000000000;
		std::istringstream iss(line);
		int n;
		byte p_cero = 0;
		int i = 15;

		while (iss >> n)
		{
			if (n == 0){
				p_cero = 15 - i;
			}
			if (i > 7) {
				representacion[0] = representacion[0] | n << 4*i ;
			} else {
				representacion[1] = representacion[1] | n << 4*i ;
			}
			i--;
		}
		long unsigned int temp = representacion[0];
		temp = (temp << 32);
		rep = temp + representacion[1];
		printf("Funcion stefano: %016llX\n", rep);
		
		nodo = new node(rep, p_cero);

		printf("Manhattan: %d \n",manhattan(nodo));
		nodo->print();
		search *s = new search();
		int sol = s->ida_star(nodo, manhattan);
		
		printf("Sol: %d\n", sol);
		

	}
	return 0;
}