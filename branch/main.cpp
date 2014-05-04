#include <stdio.h>
#include <fstream>
#include <sstream>
#include "node.h"
#include "pdb.h"
// #include "search.h"

int main(int argc, const char* argv[])
{
	std::ifstream infile(argv[1]);
	std::string line;
	long unsigned int representacion;
	node *nodo;

	while (std::getline(infile, line))
	{
		representacion = 0x0000000000000000;
		std::istringstream iss(line);
		int n;
		byte p_cero = 0;
		int i = 15;

		while (iss >> n)
		{
			if (n == 0)
				p_cero = 15 - i;
			
			representacion = representacion | n << 4*i;			
			--i;
		}
		
		nodo = new node(representacion, p_cero);
		
		//printf("Manhattan: %d \n",manhattan(nodo));
		//nodo->print();
		//search *s = new search();
		
		//int sol = s->ida_star(nodo, manhattan);
		
// 		//printf("Sol: %d\n", sol);

	}
	return 0;
}
