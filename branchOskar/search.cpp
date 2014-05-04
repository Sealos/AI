#include "search.h"

const int FOUND = -4;

byte man_data[16][16] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4, 4, 3, 4, 5},
	{2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3, 5, 4, 3, 4},
	{3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2, 6, 5, 4, 3},
	{1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5},
	{2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3, 3, 2, 3, 4},
	{3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2, 4, 3, 2, 3},
	{4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1, 5, 4, 3, 2},
	{2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3, 1, 2, 3, 4},
	{3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2, 2, 1, 2, 3},
	{4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1, 3, 2, 1, 2},
	{5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0, 4, 3, 2, 1},
	{3, 4, 5, 6, 2, 3, 4, 5, 1, 2, 3, 4, 0, 1, 2, 3},
	{4, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3, 1, 0, 1, 2},
	{5, 4, 3, 4, 4, 3, 2, 3, 3, 2, 1, 2, 2, 1, 0, 1},
	{6, 5, 4, 3, 5, 4, 3, 2, 4, 3, 2, 1, 3, 2, 1, 0}
};

int manhattan(node *n)
{
	int val = 0;
	int valor;
	for (int i = 0; i < 16; ++i)
	{
		valor = n->get_value(i);
		val += man_data[i][valor];
	}
	return val;
}

search::search()
{
	//ctor
}
/*
list<byte> search::a_star(node *n, int (*h)(node *))
{
	priority_queue<node*, vector<node*>, compare_node_mh> q;
	if (h == pdb)
		priority_queue<node*, vector<node*>, compare_node_pdb> q;
	q.push(n);
	unordered_set<node*> cerrados;

	while (!q.empty())
	{
		n = q.top();
		q.pop();

		if (!n->estado->closed || n->g < n->estado->dist)
		{
			if (n->g < n->estado->dist)
			{		printf("Guardia: %d \n", n->g);
				n->print();
		}
			n->estado->closed = true;
			n->estado->dist = n->g;
			if (n->is_goal())
			{
				return n->extract_solution();
			}

			list<byte> succ = n->succ();
			byte a;

			for (list<byte>::const_iterator iterator = succ.begin(), end = succ.end(); iterator!=end; ++iterator)
			{
				a = *iterator;
				node *np = new node(n,a,n->accion);
				if (h(np) < INT_MAX)
				{
					q.push(np);
				}
			}
		}
	}
	list<byte> l_moves;
	return l_moves;
} */


int search::ida_star(node *n, int (*h)(node *))
{
	int t = h(n);
	while (t != INT_MAX)
	{
		int bound = bonded_dfs(n, 0, t, h);
		if (bound == FOUND) { return FOUND; }
		t = bound;
		printf("Bound: %d\n", t);
	}
	return -1;
}

int search::bonded_dfs(node *n, int g, int t, int (*h)(node *))
{
	int f = g + h(n);

	if (f > t) { return f; }

	if (n->is_goal()) { return FOUND; }

	int new_t = INT_MAX;
	for (int i = 1; i <= 4; ++i)
	{
		if (n->valid_action(i))
		{
			node *np = new node(n, i, n->accion);
			int path = bonded_dfs(np, np->g, t, h);
			if (path == FOUND) { return FOUND; }
			if (path < new_t) { new_t = path; }
		}
	}
	return new_t;
}

bool compare_node_mh::operator()(node* n1, node* n2)
{
	if ((n1->g + manhattan(n1)) > (n2->g + manhattan(n2)))
		return true;
	return false;
}

bool compare_node_pdb::operator()(node* n1, node* n2)
{
	/*if ((n1->g + pdb(n1)) > (n2->g + pdb(n2)))
		return true;*/
	return false;
}
