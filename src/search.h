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

int manhattan(node *n);


class search
{
public:
search();
int a_star(node *n, int (*heuristic)(node *)); // por ahora noooo
int ida_star(node *n, int (*h)(node *));
int bonded_dfs(node *n, int g, int t, int (*h)(node *));
};

class compare_node_mh
{
public:
	bool operator()(node* n1, node* n2);
};

class compare_node_pdb
{
public:
	bool operator()(node* n1, node* n2);
};

#endif // SND_H
