#include <climits>
#include "node.h"
#include <cstdlib>
#include <vector>
#include <queue>
#include <unordered_map>

#ifndef SND_H
#define SND_H

using namespace std;

struct v_ida
{
	list<int> path;
	int g;
};

class SnD
{
public:
	SnD();
	list<int> seek(node n); //A*
	list<int> destroy(node n); //IDA*
	v_ida Bonded_DFS(node n, int g, int t);
};

#endif // SND_H
