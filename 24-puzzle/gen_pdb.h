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
#include <list>
#include <algorithm>

typedef unsigned char byte;

class node
{
public:
	byte pos_cero;
	byte accion;
	byte acc_padre;
	byte g;
	byte val[25];

	node(node *p, byte a, byte b);

	node(long unsigned int val0, byte p_cero);

	int get_value(int n);

	bool valid_action(byte a);

	void print();

	std::list<unsigned char> succ();
};

#endif // PDB_H
