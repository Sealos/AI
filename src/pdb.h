#include <fstream>
#include <vector>
#include <climits>

#ifndef PDB_H
#define PDB_H

#define SIX_FACT	57657600
#define THREE_FACT	57657600

class pdb
{
public:
	pdb();
	unsigned char h(long unsigned int val);
	long unsigned  int get_rank(long unsigned  int val);
	inline unsigned char get_value_node(long unsigned int val, unsigned char pos);
	inline long unsigned int set_value_node(long unsigned int val, unsigned char data, unsigned char pos, long unsigned int r_mask);
};

#endif // PDB_H
