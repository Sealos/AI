#include <fstream>
#include <vector>
#include <climits>

#ifndef PDB_H
#define PDB_H

#define MAX_VALUE	6375600

typedef unsigned char byte;

void pdb_init();
int pdb_h_array(unsigned char *array);
long unsigned int p_rank(int n, byte *s, byte *w, int k);
long unsigned int get_rank(byte *p, byte *fix);

#endif // PDB_H
