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
	ifstream infile(argv[1]);
	string line;
	unsigned char rep[25];

	while (std::getline(infile, line))
	{
		istringstream iss(line);
		int n;
		byte p_cero = 0;
		int i = 0;

		while (iss >> n)
			rep[i++] = n;

		search *s = new search();

		int sol = s->ida_star(rep, p_cero, manhattan_array);
		//int sol = s->ida_star(rep, p_cero, pdb_h_array);
		//int sol = s->a_star(nodo, pdb_h);
		//int sol = s->a_star(nodo, manhattan);
		sol = sol + 1;
	}
	return 0;
}
