#include "pdb.h"

using namespace std;

vector<long unsigned int> factorial(16,1);

unsigned char pdb_data_1[SIX_FACT];		//Contiene la data de 1-2-3-4-5-6
unsigned char pdb_data_2[SIX_FACT];		//Contiene la data de 7-8-9-10-11-12
unsigned char pdb_data_3[THREE_FACT];	//Contiene la data de 13-14-15

long unsigned int mask[16] =
{
	0xF000000000000000,
	0x0F00000000000000,
	0x00F0000000000000,
	0x000F000000000000,
	0x0000F00000000000,
	0x00000F0000000000,
	0x000000F000000000,
	0x0000000F00000000,
	0x00000000F0000000,
	0x000000000F000000,
	0x0000000000F00000,
	0x00000000000F0000,
	0x000000000000F000,
	0x0000000000000F00,
	0x00000000000000F0,
	0x000000000000000F
};

void pdb_init()
{
	for(int i = 1; i < 16; ++i)
		factorial[i] = i * factorial[i-1];

	ifstream f("pdb_data_123456.bin", ios::in | ios::binary);
	f.read((char *)pdb_data_1, SIX_FACT);
	f.close();

	ifstream g("pdb_data_789ABC.bin", ios::in | ios::binary);
	g.read((char *)pdb_data_2, SIX_FACT);
	g.close();

	ifstream h("pdb_data_DEF.bin", ios::in | ios::binary);
	h.read((char *)pdb_data_3, THREE_FACT);
	h.close();
}

inline unsigned char pdb_get_value_node(long unsigned int val, unsigned char pos)
{
	val = val & mask[pos];
	unsigned char value = val >> ((15 - pos) * 4);
	return value;
}

inline long unsigned int pdb_set_value_node(long unsigned int val, unsigned char data, unsigned char pos, long unsigned int r_mask)
{
	long unsigned int sum_val = (val & r_mask);
	long unsigned int new_val = data;
	new_val = new_val << ((15 - pos) * 4);
	new_val += sum_val;
	return new_val;
}

int pdb_h(long unsigned int val)
{
	unsigned char value = 0;
	unsigned char permutacion[3][16] =
	{
		{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
		{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
		{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}
	};

	long unsigned int temp;
	unsigned char r_value;
	for (int i = 0; i < 16; ++i)
	{
		temp = val & mask[i];
		r_value = temp >> ((15 - i) * 4);
		switch (r_value)
		{
		case 0:
			// Colocamos el 0 en todas las permutaciones
			for (int j = 0; j < 3; ++j)
				permutacion[j][i] = 0;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			permutacion[0][i] = r_value;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			permutacion[1][i] = r_value;
			break;
		case 13:
		case 14:
		case 15:
			permutacion[2][i] = r_value;
			break;
		}
	}
	//printf("Perm1: %016llX | Perm2: %016llX | Perm3: %016llX\n", permutacion[0], permutacion[1], permutacion[2]);

	// Calculamos el valor
	value += pdb_data_1[get_rank(permutacion[0])];
	//printf("Value: %d\n", value);
	value += pdb_data_2[get_rank(permutacion[1])];

	//printf("Value: %d\n", value);
	value += pdb_data_3[get_rank(permutacion[2])];
	//printf("Value: %d\n", value);

	return value;
}

int pdb_h_array(unsigned char *array)
{
	unsigned char value = 0;
	unsigned char permutacion[3][16] =
	{
		{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
		{0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
		{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}
	};

	unsigned char r_value;
	for (int i = 0; i < 16; ++i)
	{
		r_value = array[i];
		switch (r_value)
		{
		case 0:
			// Colocamos el 0 en todas las permutaciones
			for (int j = 0; j < 3; ++j)
				permutacion[j][i] = 0;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			permutacion[0][i] = r_value;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			permutacion[1][i] = r_value;
			break;
		case 13:
		case 14:
		case 15:
			permutacion[2][i] = r_value;
			break;
		}
	}
	//printf("Perm1: %016llX | Perm2: %016llX | Perm3: %016llX\n", permutacion[0], permutacion[1], permutacion[2]);

	// Calculamos el valor
	value += pdb_data_1[get_rank(permutacion[0])];
	//printf("Value: %d\n", value);
	value += pdb_data_2[get_rank(permutacion[1])];

	//printf("Value: %d\n", value);
	value += pdb_data_3[get_rank(permutacion[2])];
	//printf("Value: %d\n", value);

	return value;
}

long unsigned int get_rank(unsigned char *array)
{
	vector<int> freq(16);
	long unsigned int den = 1;
	long unsigned int ret = 0;
	for(int i = 15; i >= 0; --i)
	{
		int si = array[i];
		freq[si]++;
		den *= freq[si];
		for (int c = 0; c < si; ++c) 
			if(freq[c] > 0) 
				ret += factorial[15-i] / (den / freq[c]);
	}
	return ret;
}
