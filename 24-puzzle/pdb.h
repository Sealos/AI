#include <fstream>
#include <vector>
#include <climits>

#ifndef PDB_H
#define PDB_H

#define SIX_FACT	57657600
#define THREE_FACT	57657600

void pdb_init();
int pdb_h_array(unsigned char *array);
long unsigned int get_rank(unsigned char *array);

#endif // PDB_H
