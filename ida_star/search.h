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
#include "state_ida.h"

#ifndef SND_H
#define SND_H

using namespace std;

int manhattan_array(unsigned char *v);


class search
{
public:
	search();
	int ida_star(long unsigned int val, byte p_cero, int (*h)(unsigned char *));
	int bonded_dfs(int t, byte acc_pad, int (*h)(unsigned char *));
};

class compare_node
{
public:
	bool operator()(node* n1, node* n2);
};

#endif // SND_H
