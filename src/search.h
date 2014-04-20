
#include "node.h"
#include <cstdlib>

#ifndef SND_H
#define SND_H

using namespace std;

int manhattan(node *n);

struct v_ida
{
	list<unsigned char> path;
	int g;
};

class search
{
public:
	search();
	list<unsigned char> a_star(node *n, int (*heuristic)(node *)); // por ahora noooo
	list<unsigned char> ida_star(node *n, int (*h)(node *));
	v_ida bonded_dfs(node *n, int g, int t, int (*h)(node *));
};

#endif // SND_H
