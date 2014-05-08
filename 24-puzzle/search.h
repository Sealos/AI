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
#include "state_ida.h"

#ifndef SND_H
#define SND_H

using namespace std;

int manhattan_array(unsigned char *v);

class search
{
public:
	search();
	int ida_star(byte *rep, byte p_cero, int (*h)(unsigned char *));
	int bonded_dfs(int t, byte acc_pad, int (*h)(unsigned char *));
};

#endif // SND_H
