#include <cstdlib>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "pdb.h"

#ifndef SND_H
#define SND_H

using namespace std;

int manhattan(node *n);

struct v_ida
{
list<byte> path;
int g;
};

class search
{
public:
search();
list<byte> a_star(node *n, int (*heuristic)(node *)); // por ahora noooo
list<byte> ida_star(node *n, int (*h)(node *));
v_ida bonded_dfs(node *n, int g, int t, int (*h)(node *));
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
