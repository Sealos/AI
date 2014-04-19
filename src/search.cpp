#include "search.h"

int manhattan(node *n)
{
	int val = 0;
	for (int i = 0; i < 16; ++i)
	{
		int x = i mod 4;
		int y = i div 4;
		int valor = n->get_value(i);
		int xs = valor mod 4;
		int ys = valor div 4;
		val += abs(x - xs) + abs(y - ys);
	}
	return val;
}

search::search()
{
	//ctor
}

list<unsigned char> search::a_star(node *n, int (*heuristic)(node *))
{
	/*std::priority_queue<node, CONTENEDOR, COMPARADOR> q;
	q.push(n);
	unordered_map<> closed;
	while (!q.empty)
	{
		n << q.pop
		if (closed.find(n.val) != closed.end() || g(n)<dist[n.val] closed[n.val]?)
		{
			closed.insert(n.val); //closed[n.val] = g(n) ?
			dist[n.val] = g(n); //
			if (n.is_goal())
			{
				return n.extract_solution()
			}
			std::list succe = n.succ(); //Lista de las acciones para obtener los sucesores
			for (std::list<int>::const_iterator i = succe.begin(); fin = succe.end(); i!=fin; ++i)
			{
				a << *i
				if (h(s)<INT_MAX) //s debe ser el estado que se produce de aplicar la accion a sobre n
				{
					q.push(node(n,a))
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
