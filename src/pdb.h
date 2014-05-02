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
	byte get_value(unsigned long int val);
	unsigned long int get_rank(unsigned long int val);

};

#endif // PDB_H
