#include "search.h"
#include <time.h>

const long unsigned int goal = 0x0123456789ABCDEF;

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

search::search()
{
	//ctor
}

bool compare_node::operator()(node* n1, node* n2)
{
	if ((n1->g + n1->stt->heur) > (n2->g + n2->stt->heur))
		return true;
	return false;
}

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

int search::a_star(node *root, int (*h)(long unsigned int))
{
	priority_queue<node*, vector<node*>, compare_node> q;
	clock_t start,end;
	float total;
	start=clock();
	cant_nodos1 = 0;

	if (h == pdb_h)
		pdb_init();

	q.push(root);
	while (!q.empty())
	{
	    if ((((float)clock()-start)/CLOCKS_PER_SEC)>30.00)
	    {
	        printf(" NOT\n");
	        break;
	    }

		node* n = q.top();
		q.pop();
        //printf("%d ",n->stt->heur); //NOT HERE
		if (n->is_goal()) {
            //printf("dist:%u \n", n->stt->dist);
            end=clock();
			total = ((float)end-(float)start) / CLOCKS_PER_SEC;
			printf(": %u : %f : %f\n", cant_nodos1, total,  cant_nodos1/total);
            return FOUND;
        }
       // printf("Closed:%u, dist:%u<%u? \n",n->stt->closed,n->g,n->stt->dist);

		if (!(n->stt->closed) || (n->g < n->stt->dist))
		{
			n->stt->closed = true;
			n->stt->dist = n->g;

			if (n->is_goal())
			{
			    end=clock();
                total = ((float)end-(float)start) / CLOCKS_PER_SEC;
                printf(": %u : %f : %f\n", cant_nodos1, total,  cant_nodos1/total);
				return FOUND;
			}
            //++cant_nodos1; //NODOS EXPANDIDOS
			for (int i = 4; 1 <= i; --i)
			{
				if (n->valid_action(i) && i != inv(n->accion))
				{
					node *np = new node(n,i,h);
					int heu;
					heu = np->stt->heur;
					if (heu < INT_MAX)
					{
					    ++cant_nodos1; //NODOS CREADOS
                        q.push(np);
					}
				}
			}
		}
	}

	return NOT_FOUND;
}
