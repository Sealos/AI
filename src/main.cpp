#include <stdio.h>
#include <cstdlib>

int main(int argc, const char* argv[])
{
#ifdef X_64
	printf( "%d -- %d\n", sizeof(int8_t), sizeof(long int));
#else

#endif
}
