#include <stdio.h>
#include <fstream>
#include <sstream>
#include "node.h"
#include "pdb.h"
#include "search.h"

using namespace std;

int cero(long unsigned int val)
 {
 	return 0;
 }

int main(int argc, const char* argv[])
{
    int num = 1;
	ifstream infile(argv[1]);
	string line;
	unsigned int representacion[2];
	node *nodo;

	while (std::getline(infile, line))
	{
		representacion[0] = 0x00000000;
		representacion[1] = 0x00000000;
		long unsigned int rep = 0x0000000000000000;
		istringstream iss(line);
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

		nodo = new node(rep, p_cero,manhattan_val);

		
		if (num<10){
            printf("00%d : ",num);
        } else if (num<100) {
            printf("0%d : ",num);
        } else {
            printf("%d : ",num);
        }
		//printf("%001 : ",num);
		nodo->print_l();

		search *s = new search();

		//int sol = s->a_star(nodo, pdb_h);
		int sol = s->a_star(nodo, manhattan_val);

        num = num + 1;
		sol = sol + 1;
	}
	return 0;
}
