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

pdb::pdb()
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

inline byte pdb::get_value_node(long unsigned int val, byte pos)
{
	val = val & mask[pos];
	byte value = val >> ((15 - pos) * 4);
	return value;
}

inline long unsigned int pdb::set_value_node(long unsigned int val, byte data, byte pos, long unsigned int r_mask)
{
	long unsigned int sum_val = (val & r_mask);
	long unsigned int new_val = val;
	new_val = (new_val << ((15 - pos) * 4)) + sum_val;
	return new_val;
}

byte pdb::get_pdb_value(long unsigned int val)
{
	byte value = 0;
	long unsigned int permutacion[3] =
	{
		0xFFFFFFFFFFFFFFFF,
		0xFFFFFFFFFFFFFFFF,
		0x1111111111111111
	};

	long unsigned int temp;
	long unsigned int r_mask;
	byte r_value;
	for (int i = 0; i < 16; ++i)
	{
		temp = val & mask[i];
		r_value = temp >> ((15 - i) * 4);
		r_mask = ULONG_MAX - mask[i];
		switch (r_value)
		{
		case 0:
			// Colocamos el 0 en todas las permutaciones
			for (int j = 0; j < 3; ++j)
				permutacion[j] = permutacion[j] & r_mask;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			set_value_node(permutacion[0], r_value, i, r_mask);
			break;
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			set_value_node(permutacion[1], r_value, i, r_mask);
			break;
		case 13:
		case 14:
		case 15:
			set_value_node(permutacion[2], r_value, i, r_mask);
			break;
		}
	}

	// Calculamos el valor
	value += pdb_data_1[get_rank(permutacion[0])];
	value += pdb_data_2[get_rank(permutacion[1])];
	value += pdb_data_3[get_rank(permutacion[2])];

	return value;
}

long unsigned int pdb::get_rank(long unsigned int val)
{
	vector<int> freq(16);
	long unsigned int den = 1;
	long unsigned int ret = 0;
	for(int i = 15; i >= 0; --i)
	{
		byte si = get_value_node(val, i);
		freq[si]++;
		den *= freq[si];
		for (int c = 0; c < si; ++c) 
			if(freq[c] > 0) 
				ret += factorial[15-i] / (den / freq[c]);
	}
	return ret;
}
