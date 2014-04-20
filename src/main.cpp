#include <stdio.h>
#include <fstream>
#include <sstream>

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
		printf("%X, %X \n", representacion[0], representacion[1]);
		//new node(representacion[0], representacion[1]);
		//node::node(representacion[0], representacion[1])
	}

}
