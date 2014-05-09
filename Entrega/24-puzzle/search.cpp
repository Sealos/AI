#include "search.h"
#include <time.h>

const int FOUND = -4;
const int NOT_FOUND = -1;

unsigned int cant_nodos1 = 0;

byte man_data[25][25] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5, 6, 5, 4, 5, 6, 7},
	{2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5, 6, 5, 4, 5, 6},
	{3, 2, 1, 0, 1, 4, 3, 2, 1, 2, 5, 4, 3, 2, 3, 6, 5, 4, 3, 4, 7, 6, 5, 4, 5},
	{4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 7, 6, 5, 4, 3, 8, 7, 6, 5, 4},
	{1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 3, 4, 5, 6, 7},
	{2, 1, 2, 3, 4, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5, 6},
	{3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5, 4, 3, 4, 5},
	{4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 4, 3, 2, 1, 2, 5, 4, 3, 2, 3, 6, 5, 4, 3, 4},
	{5, 4, 3, 2, 1, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2, 7, 6, 5, 4, 3},
	{2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 2, 3, 4, 5, 6},
	{3, 2, 3, 4, 5, 2, 1, 2, 3, 4, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4, 5},
	{4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4, 3, 2, 3, 4},
	{5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 4, 3, 2, 1, 2, 5, 4, 3, 2, 3},
	{6, 5, 4, 3, 2, 5, 4, 3, 2, 1, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1, 6, 5, 4, 3, 2},
	{3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5},
	{4, 3, 4, 5, 6, 3, 2, 3, 4, 5, 2, 1, 2, 3, 4, 1, 0, 1, 2, 3, 2, 1, 2, 3, 4},
	{5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2, 3, 2, 1, 2, 3},
	{6, 5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 4, 3, 2, 1, 2},
	{7, 6, 5, 4, 3, 6, 5, 4, 3, 2, 5, 4, 3, 2, 1, 4, 3, 2, 1, 0, 5, 4, 3, 2, 1},
	{4, 5, 6, 7, 8, 3, 4, 5, 6, 7, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4},
	{5, 4, 5, 6, 7, 4, 3, 4, 5, 6, 3, 2, 3, 4, 5, 2, 1, 2, 3, 4, 1, 0, 1, 2, 3},
	{6, 5, 4, 5, 6, 5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1, 2},
	{7, 6, 5, 4, 5, 6, 5, 4, 3, 4, 5, 4, 3, 2, 3, 4, 3, 2, 1, 2, 3, 2, 1, 0, 1},
	{8, 7, 6, 5, 4, 7, 6, 5, 4, 3, 6, 5, 4, 3, 2, 5, 4, 3, 2, 1, 4, 3, 2, 1, 0}
};

int manhattan_array(unsigned char *v)
{
	int val = 0;
	for (int i = 0; i < 25; ++i)
		val += man_data[v[i]][i];
	return val;
}

search::search()
{
	//ctor
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

int search::ida_star(byte *rep, byte p_cero, int (*h)(unsigned char *))
{
	if (h == pdb_h_array)
		pdb_init();

	clock_t start,end;
	float total;
	start=clock();

	global_state = new state_ida(rep, p_cero, h);
	
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
			printf("Nodos creados %d, Tiempo: %f, Nodos/s: %f\n", cant_nodos1, total,  cant_nodos1/total);
			cant_nodos1 = 0;
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
