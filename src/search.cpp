#include "search.h"

const int FOUND = -4;
const int NOT_FOUND = -1;
int k;

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

pdb *p;

int manhattan(node *n)
{
	int val = 0;
	int valor;
	for (int i = 0; i < 16; ++i)
	{
		valor = n->get_value(i);
		val += man_data[valor][i];
	}
	return val;
}

search::search()
{
	//ctor
}

 int search::a_star(node *n, int (*h)(node *))
{
	priority_queue<node*, vector<node*>, compare_node_mh> q;

	/*if (h == pdb)
		priority_queue<node*, vector<node*>, compare_node_pdb> q;*/

	q.push(n);
	unordered_map<long unsigned int, int> dist;
	unordered_set<node*> closed;
	
	while (!q.empty())
	{
		n = q.top();
		q.pop();
		
		if (n->is_goal()) { return FOUND; }
 		
		if (closed.find(n) == closed.end() || n->g < dist[n->val])
		{
			closed.insert(n);
			dist[n->val] = n->g;
			//printf("DistInterna: %u, %d\n", dist[n->val], n->g);
			if (n->is_goal()) { return FOUND; }
					
			for (int i = 4; 1 <= i; --i)
			{
				if (n->valid_action(i))
				{
					node *np = new node(n,i,n->accion);
					if (h(np) < INT_MAX) { q.push(np); }
				}
			}
		}
	}
	
	return NOT_FOUND;
}

bool compare_node_mh::operator()(node* n1, node* n2)
{
	if ((n1->g + manhattan(n1)) > (n2->g + manhattan(n2))) {
		return true; 
	}
	return false;
}

	
int search::ida_star(node *n, int (*h)(node *))
{
	int t = h(n);
	p = new pdb();
	while (t != INT_MAX)
	{
		int bound = bonded_dfs(n, 0, t, h);
		if (bound == FOUND) { return FOUND; }
		t = bound;
		printf("Bound: %d\n", t);
	}
	return NOT_FOUND;
}

int search::bonded_dfs(node *n, int g, int t, int (*h)(node *))
{
	int f = g + h(n);
	//printf("Mah : %d, g: %d\n", h(n), g);
	
	if (f > t)
	{
		return f;
	}
	
	if (n->is_goal()) { return FOUND; }

	int new_t = INT_MAX;
	
	for (int i = 1; i <= 4; ++i)
	{
		if (n->valid_action(i))
		{
			node *np = new node(n, i, n->accion);
			if (np->val == n->val)
				delete np;
			else
			{
				int cost = bonded_dfs(np, np->g, t, h);
				delete np;
				if (cost == FOUND)
					return FOUND;
				new_t = min(new_t, cost);
			}
		}
	}
	return new_t;
}


bool compare_node_pdb::operator()(node* n1, node* n2)
{
	/*if ((n1->g + p->get_pdb_value(n1->val) > (n2->g + p->get_pdb_value(n2->val))
		return true;*/
	return false;
}
