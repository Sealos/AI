#include <cstdlib>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include "pdb.h"
#include "node.h"

#ifndef SND_H
#define SND_H

using namespace std;

int manhattan_val(long unsigned int v);

class search
{
public:
	search();
	int a_star(node *n, int (*h)(long unsigned int));
};

class compare_node
{
public:
	bool operator()(node* n1, node* n2);
};

#endif // SND_H
