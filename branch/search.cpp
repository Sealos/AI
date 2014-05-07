#include "search.h"
#include <time.h>

const long unsigned int goal = 0x0123456789ABCDEF;

const int FOUND = -4;
const int NOT_FOUND = -1;

long unsigned int cant_nodos1 = 0;

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

long unsigned int m[16] =
{
	0xF000000000000000,
	0x0F00000000000000,
	0x00F0000000000000,
	0x000F000000000000,
	0x0000F00000000000,
	0x00000F0000000000,
	0x000000F000000000,
	0x0000000F00000000,
	0x00000000F0000000,
	0x000000000F000000,
	0x0000000000F00000,
	0x00000000000F0000,
	0x000000000000F000,
	0x0000000000000F00,
	0x00000000000000F0,
	0x000000000000000F
};

inline unsigned char get_value_node(long unsigned int val, unsigned char pos)
{
	val = val & m[pos];
	unsigned char value = val >> ((15 - pos) * 4);
	return value;
}

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

int manhattan_val(long unsigned int v)
{
	int val = 0;
	int valor;
	for (int i = 0; i < 16; ++i)
	{
		valor = get_value_node(v, i);
		val += man_data[valor][i];
	}
	return val;
}

int manhattan_array(unsigned char *v)
{
	int val = 0;
	for (int i = 0; i < 16; ++i)
		val += man_data[v[i]][i];
	return val;
}

search::search()
{
	//ctor
}

int search::a_star(node *n, int (*h)(long unsigned int))
{
	/*priority_queue<node*, vector<node*>, compare_node> q;

	unordered_map<long unsigned int, int> dist;

	if (h == pdb_h)
		pdb_init();
	q.push(n);

	while (!q.empty())
	{
		n = q.top();
		q.pop();

		if (n->is_goal()) { return FOUND; }


		if (!n->stt->closed || n->g < dist[n->stt->val])
		{

			n->stt->closed = true;
			dist[n->stt->val] = n->g;

			if (n->is_goal())
			{
				return FOUND;
			}

			for (int i = 4; 1 <= i; --i)
			{
				if (n->valid_action(i))
				{
					node *np = new node(n,i,h);
					int heu;
					heu = np->stt->heur;
					if (heu < INT_MAX) { q.push(np); }
				}
			}
		}
	}

	*/return NOT_FOUND;
}

bool compare_node::operator()(node* n1, node* n2)
{
	if ((n1->g + n1->stt->heur) > (n2->g + n2->stt->heur))
		return true;
	return false;
}

state_ida *global_state;

byte inv(byte a)
{
	switch (a)
	{
	case MOV_ARRIBA:
		return MOV_ABAJO;
	case MOV_ABAJO:
		return MOV_ARRIBA;
	case MOV_DER:
		return MOV_IZQ;
	case MOV_IZQ:
		return MOV_DER;
	default:
		return MOV_NULL;
	}
}

int search::ida_star(long unsigned int val, byte p_cero, int (*h)(unsigned char *))
{
	if (h == pdb_h_array)
		pdb_init();

	clock_t start,end;
	float total;
	start=clock();
	cant_nodos1 = 0;

	global_state = new state_ida(val, p_cero, h);
	
	int t = global_state->heur;
	printf("Bound: %d\n", t);
	while (t != INT_MAX)
	{
		int bound = bonded_dfs(t, 0, h);
		if (bound == FOUND)
		{
			end=clock();
			total = ((float)end-(float)start) / CLOCKS_PER_SEC;
			delete global_state;
			printf("--Found--\n");
			printf("Nodos creados %lu, Tiempo: %f, Nodos/s: %f\n", cant_nodos1, total,  cant_nodos1/total);
			return FOUND;
		}
		t = bound;
		printf("Bound: %d\n", t);
	}
	return NOT_FOUND;
}

int search::bonded_dfs(int t, byte acc_pad, int (*h)(unsigned char *))
{
	int f = global_state->dist + global_state->heur;

	if (f > t)
	{
		return f;
	}

	if (global_state->is_goal()) { return FOUND; }

	int new_t = INT_MAX;
	byte h_tmp;

	for (int i = 1; i <= 4; ++i)
	{
		if (global_state->valid_action(i) && i != inv(acc_pad))
		{
				h_tmp = global_state->heur;
				global_state->apply_action(i, h);
				global_state->dist = global_state->dist + 1;
				global_state->heur = h(global_state->val);
				++cant_nodos1;
				int cost = bonded_dfs(t, i, h);
				global_state->heur = h_tmp;
				global_state->apply_action(inv(i), h);
				global_state->dist = global_state->dist - 1;

				if (cost == FOUND)
					return FOUND;
				new_t = min(new_t, cost);
		}
	}
	return new_t;
}
