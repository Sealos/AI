#include "pdb.h"

using namespace std;

#define PERM_SIZE	5
#define N			25

byte fix[6][5] =
{
	{0, 1, 2, 3, 4},
	{0, 5, 6, 7, 8},
	{0, 9 , 10, 11 ,12},
	{0, 13, 14, 15, 16},
	{0, 17, 18, 19, 20},
	{0, 21, 22, 23, 24}
};

byte pdb_data[6][MAX_VALUE];

void pdb_init()
{
	ifstream f("pdb_data_0.bin", ios::in | ios::binary);
	f.read((char *)pdb_data[0], MAX_VALUE);
	f.close();

	ifstream a("pdb_data_1.bin", ios::in | ios::binary);
	a.read((char *)pdb_data[1], MAX_VALUE);
	a.close();

	ifstream b("pdb_data_2.bin", ios::in | ios::binary);
	b.read((char *)pdb_data[2], MAX_VALUE);
	b.close();
	
	ifstream c("pdb_data_3.bin", ios::in | ios::binary);
	c.read((char *)pdb_data[3], MAX_VALUE);
	c.close();
	
	ifstream d("pdb_data_4.bin", ios::in | ios::binary);
	d.read((char *)pdb_data[4], MAX_VALUE);
	d.close();
	
	ifstream e("pdb_data_5.bin", ios::in | ios::binary);
	e.read((char *)pdb_data[5], MAX_VALUE);
	e.close();
}

int pdb_h_array(unsigned char *array)
{
	unsigned char value = 0;
	unsigned char permutacion[6][25] =
	{
		{25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
		{25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
		{25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
		{25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
		{25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
		{25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25}
	};

	unsigned char r_value;
	for (int i = 0; i < 25; ++i)
	{
		r_value = array[i];
		switch (r_value)
		{
		case 0:
			// Colocamos el 0 en todas las permutaciones
			for (int j = 0; j < 6; ++j)
				permutacion[j][i] = 0;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			permutacion[0][i] = r_value;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			permutacion[1][i] = r_value;
			break;
		case 9:
		case 10:
		case 11:
		case 12:
			permutacion[2][i] = r_value;
			break;
		case 13:
		case 14:
		case 15:
		case 16:
			permutacion[3][i] = r_value;
			break;
		case 17:
		case 18:
		case 19:
		case 20:
			permutacion[4][i] = r_value;
			break;
		case 21:
		case 22:
		case 23:
		case 24:
			permutacion[5][i] = r_value;
			break;
		}
	}

	long unsigned int vl;
	for (int i = 0; i < 6; ++i)
		value += pdb_data[i][get_rank(permutacion[i], fix[i])];

	return value;
}

long unsigned int p_rank(int n, byte *s, byte *w, int k)
{
	if(n == 1 || k == 0)
		return 0;
	int d = s[n - 1];
	byte tmp = s[n-1];
	s[n - 1] = s[w[n - 1]];
	s[w[n - 1]] = tmp;

	tmp = w[n - 1];
	w[n - 1] = w[d];
	w[d] = tmp;
	unsigned long int h = p_rank(n - 1, s, w, k - 1);
	unsigned long int r = (d + (n * h));
	return r;
}

long unsigned int get_rank(byte *p, byte *fix)
{
	byte odr[N] =
	{
		0, 1, 2, 3, 4,
		5, 6, 7, 8, 9,
		10, 11, 12, 13, 14,
		15, 16, 17, 18, 19,
		20, 21, 22, 23, 24
	};

	byte actual = 0;
	int j;
	for (int i = 0; i < N; ++i)
	{
		if ((p[i] >= fix[1] && p[i] <= fix[4]) || p[i] == 0)
		{
			for (j = 0; j < PERM_SIZE; ++j)
				if (fix[j] == p[i])
				{ 
					odr[j + N - PERM_SIZE] = i;
					break;
				}
		}
		else
			odr[actual++] = i;
	}

	byte t[N];
	byte q[N];
	for (int i = 0; i < N; ++i)
	{
		t[i] = odr[i];
		q[odr[i]] = i;
	}

	long unsigned int m = p_rank(N, t, q, PERM_SIZE);
	return m;
}
