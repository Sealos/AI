#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include "define.h"


int main(int argc, const char* argv[])
{
	std::ifstream infile(argv[1]);
	std::string line;
	unsigned int representacion[2] = { 0x00000000, 0x00000000 };
	
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int n;
		int i = 15;
		
		while (iss >> n)
		{
			if (i > 7) {
				representacion[0] = representacion[0] | n << 4*i ; 
			} else {
				representacion[1] = representacion[1] | n << 4*i ;
			}
			i--;
		}
		
		//node::node(representacion[0], representacion[1])
	}
	
}
