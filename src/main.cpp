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

	while (std::getline(infile, line))
	{
		representacion[0] = 0x00000000;
		representacion[1] = 0x00000000;
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
		//printf("%X, %X \n", representacion[0], representacion[1]);
		node *nodo = new node(representacion[0], representacion[1], p_cero);
		printf("Manhattan: %d \n",manhattan(nodo));
		nodo->print();
		pdb *p = new pdb();
		printf("PDB %i\n", p->get_pdb_value(nodo->val));
		//search *s = new search();
		//int succ = s->ida_star(nodo, manhattan);
		
		//printf("Sol: %d", succ);
		
		return 0;

	}

}
