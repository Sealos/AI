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

class node
{
public:
	unsigned char pos_cero;
	unsigned char accion;
	unsigned char acc_padre;
	unsigned char g;
	unsigned long int val;

	node(node *p, unsigned char a, unsigned char b);

	node(unsigned long int val0, unsigned char p_cero);

	int get_value(int n);

	unsigned long int get_rank();
	unsigned long int get_rank_blai();

	void set_value(unsigned char val, unsigned char pos);

	unsigned long int get_rank(node *p);
	
	bool valid_action(unsigned char a);

	void print();
};

#endif // PDB_H
