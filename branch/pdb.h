#include <fstream>
#include <vector>
#include <climits>

#ifndef PDB_H
#define PDB_H

#define SIX_FACT	57657600
#define THREE_FACT	57657600

void pdb_init();
int pdb_h(long unsigned int val);
int pdb_h_array(unsigned char *array);
long unsigned int get_rank(unsigned char *array);
inline unsigned char pdb_get_value_node(long unsigned int val, unsigned char pos);
inline long unsigned int pdb_set_value_node(long unsigned int val, unsigned char data, unsigned char pos, long unsigned int r_mask);


#endif // PDB_H
