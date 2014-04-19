#include "SnD.h"

SnD::SnD()
{
	//ctor
}

list<int> SnD::seek(node n)
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
	list<int> l_moves;
	return l_moves;
}

list<int> SnD::destroy(node n)
{
	/*t = g(n) + h(n);
	while (t!=INT_MAX)
	{
		<plan,tp> = Bonded_DFS(n,0,t);
		if (plan!=NULL)
		{
			return plan;
		}
		t = tp;
	}*/
}

v_ida SnD::Bonded_DFS(node n, int g, int t)
{
	/*if (g(n)+h(n)>t)
	{
		return <NULL,g(n)+h(n)>;
	}
	if (n.is_goal())
	{
		return <n.extract_solution(),g(n)>
	}
	tp = INT_MAX
	std::list succe = n.succ(); //Lista de las acciones para obtener los sucesores
	for (std::list<int>::const_iterator i = succe.begin(); fin = succe.end(); i!=fin; ++i)
	{
		a << *i;
		node np = node(n,a);
		<plan,tp> = Bonded_DFS(np,g(np),tp);
		if (plan != NULL);
		{
			return <plan,tp>;
		}
		new_t = min(new_t,tp);
	}*/
	v_ida a;
	return a;
}
