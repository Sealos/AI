#ifndef PDB_H
#define PDB_H
#include <stdio.h>
#include <climits>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>

typedef unsigned char byte;

class node
{
public:
	byte pos_cero;
	byte accion;
	byte acc_padre;
	byte g;
	unsigned long int val;

	node(node *p, byte a, byte b);

	node(unsigned long int val0, byte p_cero);

	int get_value(int n);

	unsigned long int get_rank();
	unsigned long int get_rank_blai();

	void set_value(byte val, byte pos);

	unsigned long int get_rank(node *p);
	
	bool valid_action(byte a);

	void print();
};

#endif // PDB_H
