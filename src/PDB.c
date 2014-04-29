#include <stdio.h>
#include <stdlib.h>
#define SWAP(a,b) do{t=(a);(a)=(b);(b)=t;}while(0)

int _mr_rank1(int n, int *vec, int *inv)
{
    int s, t;
    if (n < 2) return 0;
 
    s = vec[n-1];
    SWAP(vec[n-1], vec[inv[n-1]]);
    SWAP(inv[s], inv[n-1]);
    return s + n * _mr_rank1(n-1, vec, inv);
}

long int get_rank(int n, byte *vec)
{
    int i, r, *v, *inv;
 
    v = malloc(n * sizeof(int));
    inv = malloc(n * sizeof(int));
 
    for (i = 0; i < n; ++i) {
        v[i] = vec[i];
        inv[vec[i]] = i;
    }
    r = _mr_rank1(n, v, inv);
    free(inv);
    free(v);
    return r;
}

int calcular_manhattan(int val1, int val2, int val3, int val4, int pos1, int pos2, int pos3, int pos4)
{
	int val = 0;

	int x = (val1) % 4;
	int y = (val1) / 4;
	int xs = (pos1) % 4;
	int ys = (pos1) / 4;
	val += abs(x - xs) + abs(y - ys);

	x = (val2) % 4;
	y = (val2) / 4;
	xs = (pos2) % 4;
	ys = (pos2) / 4;
	val += abs(x - xs) + abs(y - ys);

	x = (val3) % 4;
	y = (val3) / 4;
	xs = (pos3) % 4;
	ys = (pos3) / 4;
	val += abs(x - xs) + abs(y - ys);

	x = (val4) % 4;
	y = (val4) / 4;
	xs = (pos4) % 4;
	ys = (pos4) / 4;
	val += abs(x - xs) + abs(y - ys);

	return val;
}

int main(int argc, const char* argv[])
{
	int a, b, c, d;
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
							{
								a = calcular_manhattan(i, j, k, l, 0, 1, 4, 5);
								b = calcular_manhattan(i, j, k, l, 2, 3, 6, 7);
								c = calcular_manhattan(i, j, k, l, 8, 9, 12, 13);
								d = calcular_manhattan(i, j, k, l, 10, 11, 14, 15);
								printf("{%d, %d, %d, %d}, {%d, %d, %d, %d}\n", i, j, k, l, a, b, c, d);
							}
						}
				}
		}
	}
}
