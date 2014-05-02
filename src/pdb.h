#include "node.h"
#include <fstream>
#include <vector>

#ifndef PDB_H
#define PDB_H

#define SIX_FACT	57657600
#define THREE_FACT	57657600

class pdb
{
public:
	pdb();
	byte get_pdb_value(long unsigned int val);
	long unsigned  int get_rank(long unsigned  int val);
	inline byte get_value_node(long unsigned int val, byte pos);
	inline long unsigned int set_value_node(long unsigned int val, byte data, byte pos, long unsigned int r_mask);
};

#endif // PDB_H
