#include "search.h"

const int FOUND = -4;
const int NOT_FOUND = -1;

unsigned int cant_nodos1 = 0;

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

    if ( h != manhattan )
		priority_queue<node*, vector<node*>, compare_node_pdb> q;
		p = new pdb();
	q.push(n);
	unordered_map<long unsigned int, int> dist;

	while (!q.empty())
	{
		n = q.top();
		q.pop();

		if (n->is_goal()) { return FOUND; }


		if (!n->stt->closed || n->g < dist[n->stt->val])
		{

			n->stt->closed = true;
			dist[n->stt->val] = n->g;

			if (n->is_goal()) { return FOUND; }

			for (int i = 4; 1 <= i; --i)
			{
				if (n->valid_action(i))
				{
					node *np = new node(n,i);
					int heu;
					if (h == manhattan)
                    {
                        heu = h(np);
                    }else
                    {
                        heu = p->h(np->stt->val);
                    }
					if (heu < INT_MAX) { q.push(np); }
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

bool compare_node_pdb::operator()(node* n1, node* n2)
{
	if ((n1->g + p->h(n1->stt->val) > (n2->g + p->h(n2->stt->val)) ))
		return true;
	return false;
}

	
int search::ida_star(node *n, int (*h)(node *))
{
	int t = 0;
	if (h == manhattan)
		t = h(n);
	else {
		p = new pdb();
		t = p->h(n->stt->val);
	}

	while (t != INT_MAX)
	{
		int bound = bonded_dfs(n, 0, t, h);
		if (bound == FOUND) 
		{
			return FOUND; 
		}
		t = bound;
		printf("Bound: %d\n", t);
	}
	return NOT_FOUND;
}

int search::bonded_dfs(node *n, int g, int t, int (*h)(node *))
{
	int f = 0;
	if (h == manhattan){
		f = g + h(n);
	} else {
		f = g + p->h(n->stt->val);
	}

	
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
			node *np = new node(n, i);
			if (np->stt->val == n->stt->val)
			{
				delete np->stt;
				delete np;
			}
			else
			{
				int cost = bonded_dfs(np, np->g, t, h);
				delete np->stt;
				delete np;
				if (cost == FOUND)
					return FOUND;
				new_t = min(new_t, cost);
			}
		}
	}
	return new_t;
}
