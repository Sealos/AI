#include "search.h"

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


/* list<byte> search::a_star(node *n, int (*h)(node *))
{
	priority_queue<node*, vector<node*>, compare_node_mh> q;

	if (h == pdb)
		priority_queue<node*, vector<node*>, compare_node_pdb> q;

	q.push(n);
	unordered_map<int, int> dist;
	unordered_set<node*> closed;
	node *n1 = new node(n, 0);
	dist[n1->hash()] = 20;
	printf("%d %d\n", n->g, n1->g);
	n->print();
	n1->print();
	printf("Guardia: %d \n", dist[n->hash()]);

	while (!q.empty())
	{
		n = q.top();
		q.pop();
		
		if (closed.find(n) == closed.end() || n->g < dist[n->hash()])
		{
			if (n->g < dist[n->hash()])
			{		printf("Guardia: %d \n", n->g);
				n->print();
		}
			closed.insert(n);
			dist[n->hash()] = n->g;
			if (n->is_goal())
			{
				return n->extract_solution();
			}

			list<byte> succ = n->succ(); //Lista de las acciones para obtener los sucesores
			byte a;

			for (list<byte>::const_iterator iterator = succ.begin(), end = succ.end(); iterator!=end; ++iterator)
			{
				a = *iterator;
				node *np = new node(n,a,n->accion);
				if (h(np) < INT_MAX) //s debe ser el estado que se produce de aplicar la accion a sobre n
				{
					q.push(np);
				}
			}
		}
	}
	list<byte> l_moves;
	return l_moves;
}

	*/
	
list<byte> search::ida_star(node *n, int (*h)(node *))
{
	int t = h(n);
	while (t != INT_MAX)
	{
		v_ida vec = bonded_dfs(n, 0, t, h);
		if (!vec.path.empty())
		{
			return vec.path;
		}
		t = vec.g;
	}
	list<byte> a;
	return a;
}

v_ida search::bonded_dfs(node *n, int g, int t, int (*h)(node *))
{
	int f = n->g + h(n);
	v_ida v;
	
	if (f > t)
	{
		list<byte> k;
		v.path = k;
		v.g = f;
		return v;
	}

	if (n->is_goal())
	{
		//v.path = n->extract_solution();
		v.path = list<byte> (4,1);
		v.g = g;
		return v;
	}

	int new_t = INT_MAX;
	/*list<byte> succ = n->succ();
	byte a;
	for (list<byte>::const_iterator iterator = succ.begin(), end = succ.end(); iterator != end; ++iterator)
	{
		a = *iterator;
		node *np = new node(n, a, n->accion);
		v_ida vec = bonded_dfs(np, np->g, t, h);
		delete np;
		if (!vec.path.empty())
		{
			return vec;
		}
		new_t = min(new_t,vec.g);
	}*/
	
	for (byte i = 1; i <= 4; ++i)
	{
		if (n->valid_action(i))
		{
			node *np = new node(n, i, n->accion);
			v_ida vec = bonded_dfs(np, np->g, t, h);
			if (!vec.path.empty())
			{
				return vec;
			}
			new_t = min(new_t,vec.g);
		}
	}
	
	v_ida l;
	return l;
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
