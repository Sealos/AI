#include <stdio.h>
#include <cstdlib>

int main(int argc, const char* argv[])
{
#ifdef X_64
	printf( "ola 64 bits\n");
#else
	printf( "ola 32 bits\n");
#endif
}
