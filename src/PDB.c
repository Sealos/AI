#include <stdio.h>

int main(int argc, const char* argv[])
{
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			if (j != i)
				for (int k = 0; k < 16; ++k)
				{
					if (k != j && k != i)
					for (int l = 0; l < 16; ++l)
						{
							if (l != k && l != j && l != i)
								printf("{%d, %d, %d, %d},\n", i, j, k, l);
						}
				}
		}
	}
}
