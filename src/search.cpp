#include "search.h"

unsigned char man_data[16][16] =
{
	{0, 1, 2, 3, 1, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6},
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
	for (int i = 0; i < 16; ++i)
	{
		int x = i % 4;
		int y = i / 4;
		int valor = n->get_value(i);
		val += man_data[i][valor];
	}
	return val;
}

search::search()
{
	//ctor
}

 list<unsigned char> search::a_star(node *n, int (*heuristic)(node *))
{
	/*priority_queue<node*, vector<node*>, compare_node> q;
	q.push(n);
	unordered_map<key,valuetype,hashfunc,equalfunc> closed;
	while (!q.empty())
	{
		n = q.pop();
		if (closed.find(n->val) != closed.end() || n->g<dist[n->val] )//closed[n->val]?
		{
			closed.insert(n->val); //closed[n->val] = n->g ?
			dist[n->val] = n->g; //
			if (n->is_goal())
			{
				return n->extract_solution();
			}
			list<unsigned char> succ = n->succ(); //Lista de las acciones para obtener los sucesores
			unsigned char a;
			for (list<unsigned char>::const_iterator iterator = succ.begin(), end = succ.end(); iterator!=end; ++iterator)
			{
				a = *iterator;
				if (h(s)<INT_MAX) //s debe ser el estado que se produce de aplicar la accion a sobre n
				{
					q.push(node(*n,a));
				}
			}
		}
	}*/
	list<unsigned char> l_moves;
	return l_moves;
}

list<unsigned char> search::ida_star(node *n, int (*h)(node *))
{
	int t = n->g + h(n);
	while (t != INT_MAX)
	{
		v_ida vec = bonded_dfs(n, 0, t, h);
		if (!vec.path.empty())
		{
			return vec.path;
		}
		t = vec.g;
	}
	list<unsigned char> a;
	return a;
}

v_ida search::bonded_dfs(node *n, int g, int t, int (*h)(node *))
{
	int f = g + h(n);
	v_ida v;

	if (f > t)
	{
		list<unsigned char> k;
		v.path = k;
		v.g = f;
		return v;
	}

	if (n->is_goal())
	{
		v.path = n->extract_solution();
		v.g = g;
		return v;
	}

	int new_t = INT_MAX;
	list<unsigned char> succ = n->succ();
	unsigned char a;
	for (list<unsigned char>::const_iterator iterator = succ.begin(), end = succ.end(); iterator != end; ++iterator)
	{
		a = *iterator;
		node *np = new node(n, a);
		v_ida vec = bonded_dfs(np, np->g, t, h);
		if (!vec.path.empty())
		{
			return vec;
		}
		new_t = min(new_t,vec.g);
	}
	v_ida l;
	return l;
}
