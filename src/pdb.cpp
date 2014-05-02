#include "pdb.h"

using namespace std;

vector<unsigned long int> factorial(16,1);

unsigned char pdb_data_1[SIX_FACT];		//Contiene la data de 1-2-3-4-5-6
unsigned char pdb_data_2[SIX_FACT];		//Contiene la data de 7-8-9-10-11-12
unsigned char pdb_data_3[THREE_FACT];	//Contiene la data de 13-14-15

unsigned long int mask[16] =
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

byte pdb::get_value(unsigned long int val)
{
	byte value = 0;

	return value;
}

unsigned long int pdb::get_rank(unsigned long int val)
{
	vector<int> freq(16);
	unsigned long int den = 1;
	unsigned long int ret = 0;
	for(int i = 15; i >= 0; --i)
	{
		int si = this->get_value(i);
		freq[si]++;
		den *= freq[si];
		for (int c = 0; c < si; ++c) 
			if(freq[c] > 0) 
				ret += factorial[15-i] / (den / freq[c]);
	}
	return ret;
}
