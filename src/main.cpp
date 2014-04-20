#include <stdio.h>
#include <fstream>
#include <sstream>
#include "node.h"

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
		unsigned char p_cero;
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
/*		printf("%X, %X \n", representacion[0], representacion[1]);
		node *nodo = new node(representacion[0], representacion[1], p_cero);
		printf("%X, %X, %d\n", nodo->val[0], nodo->val[1], nodo->g);
		printf("%X, %X, %d\n", nodo->val[0], nodo->val[1], nodo->g);
 		std::list<unsigned char>::iterator vec_int_iter;
 		vec_int_iter = k.begin();
 		for(; vec_int_iter != k.end(); vec_int_iter++)
 			printf("%u\n", *vec_int_iter);
*/	}

}
