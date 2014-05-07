#include "gen_pdb.h"

#define  EQUIS	0xFF

#define MOV_NULL	0
#define MOV_ARRIBA	1
#define MOV_ABAJO	2
#define MOV_DER		3
#define MOV_IZQ		4

#define MAX_VALUE	127512000
#define N			25
#define PERM_SIZE	6
#define MIN_PERM	1
#define MAX_PERM	5

using namespace std;

byte pdb_data[MAX_VALUE];

long unsigned int counter = 0;

long unsigned int get_rank_aux(int p[], int q[], int n)
{
	if (n <= (N - PERM_SIZE))
		return 0;
	else
	{
		int t = p[n - 1];
		swap(p[n - 1], p[q[n - 1]]);
		swap(q[t], q[n - 1]);
		return t + n * get_rank_aux(p, q, n - 1);
	}
}

long unsigned int get_rank(byte *p, byte *fix)
{
	byte odr[N] =
	{
		0, 1, 2, 3, 4,
		5, 6, 7, 8, 9,
		10, 11, 12, 13, 14,
		15, 16, 17, 18, 19,
		20, 21, 22, 23, 24
	};

	byte actual = 0;
	for (int i = 0; i < N; ++i)
	{
		if (i >= MIN_PERM || i <= MAX_PERM || i == 0)
		{
			byte k = fix[i] + N - PERM_SIZE;
			printf("%d\n", k);
			odr[k] = i;
		}
		else
			odr[actual++] = i;
	}
	for(int i = 0; i< N; ++i)
		printf("%d ", odr[i]);
	cout << endl;
	return 0;
	int t[N];
	int q[N];
	return 0;
	for (int i = 0; i < N; ++i)
	{
		t[i] = odr[i];
		q[odr[i]] = i;
	}
	return get_rank_aux(t, q, N);
}

node::node(node *p, byte a, byte b)
{
	this->accion = a;
	for (int i = 0; i < N; ++i)
		this->val[i] = p->val[i];
	this->acc_padre = b;

	switch (a)
	{
	case MOV_ARRIBA:
		this->pos_cero = p->pos_cero - 5;
		break;
	case MOV_ABAJO:
		this->pos_cero = p->pos_cero + 5;
		break;
	case MOV_DER:
		this->pos_cero = p->pos_cero + 1;
		break;
	case MOV_IZQ:
		this->pos_cero = p->pos_cero - 1;
		break;
	case MOV_NULL:
		this->pos_cero = p->pos_cero;
		return;
	}

	int val = this->val[this->pos_cero];
	if (val != EQUIS)
		this->g = p->g + 1;
	else
		this->g = p->g;
	this->val[this->pos_cero] = 0;
	this->val[p->pos_cero] = val;
}

node::node(byte *val0, byte p_cero)
{
	for (int i = 0; i < N; ++i)
		this->val[i] = val0[i];
	this->pos_cero = p_cero;
	this->acc_padre = MOV_NULL;
	this->accion = MOV_NULL;
	this->g = 0;
}

byte inv(byte a)
{
	switch(a)
	{
	case MOV_ABAJO:
		return MOV_ARRIBA;
	case MOV_ARRIBA:
		return MOV_ABAJO;
	case MOV_DER:
		return MOV_IZQ;
	case MOV_IZQ:
		return MOV_DER;
	default:
		return MOV_NULL;
	}
}

bool node::valid_action(byte a)
{
	//if (inv(a) == this->acc_padre)
	//	return false;
	switch(this->pos_cero)
	{
	case 0:
		switch(a)
		{
		case MOV_ABAJO:
		case MOV_DER:
			return true;
		default:
			return false;
		}
	case 1:
	case 2:
	case 3:
		switch(a)
		{
		case MOV_ARRIBA:
			return false;
		default:
			return true;
		}
	case 4:
		switch(a)
		{
		case MOV_ABAJO:
		case MOV_IZQ:
			return true;
		default:
			return false;
		}
	case 5:
	case 10:
	case 15:
		switch(a)
		{
		case MOV_IZQ:
			return false;
		default:
			return true;
		}
	case 6:
	case 7:
	case 8:
	case 11:
	case 12:
	case 13:
	case 16:
	case 17:
	case 18:
		return true;
	case 9:
	case 14:
	case 19:
		switch(a)
		{
		case MOV_DER:
			return false;
		default:
			return true;
		}
	case 20:
		switch(a)
		{
		case MOV_ARRIBA:
		case MOV_DER:
			return true;
		default:
			return false;
		}
	case 21:
	case 22:
	case 23:
		switch(a)
		{
		case MOV_ABAJO:
			return false;
		default:
			return true;
		}
	case 24:
		switch(a)
		{
		case MOV_ARRIBA:
		case MOV_IZQ:
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}

void node::print()
{
	printf("Pos cero: %d\n", this->pos_cero);
	for (int i = 0; i < N; ++i)
	{
		printf("%2d ", this->val[i]);
		if (i % 5 == 0)
			printf("\n");
	}
}

void write_bin(string fname)
{
	ofstream myfile;
	myfile.open (fname);
	myfile.write((const char*)&pdb_data, MAX_VALUE);
}

void bfs(node *p, byte *fix)
{
	queue<node *> Q;
	Q.push(p);
	unsigned long int rank;
	while(!Q.empty())
	{
		node *actual = Q.front();
		Q.pop();
		rank = get_rank(actual->val, fix);
		if (pdb_data[rank] > actual->g)
		{
			//actual->print();
			//printf("Val %d \n\n", actual->g);
			pdb_data[rank] = actual->g;
			++counter;
			for (byte i = 1; i <= 4; ++i)
			{
				if (actual->valid_action(i))
				{
					p = new node(actual, i, actual->accion);
					Q.push(p);
				}
			}
		}


		delete actual;
	}
}

void rellenar_arreglo()
{
	for (long unsigned int i = 0; i < MAX_VALUE; ++i)
	{
		pdb_data[i] = 0xFF;
	}
}

int main(int argc, const char** argv)
{
	byte val[5][N] =
	{
		{
			0,
			//1, 2, 3, 4, 5
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			3, 2, 1, 4, 5,
			255, 255, 255, 255
		},
		{
			0,
			255, 255, 255, 255, 255,
			6, 7, 8, 9, 10,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			255, 255, 255, 255
		},
		{
			0,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			11, 12, 13, 14, 15,
			255, 255, 255, 255, 255,
			255, 255, 255, 255
		},
		{
			0,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			16, 17, 18, 19, 20,
			255, 255, 255, 255
		},
		{
			0,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			255, 255, 255, 255, 255,
			21, 22, 23, 24
		}
	};
	byte fix[5][PERM_SIZE] =
	{
		{0, 1, 2, 3, 4, 5},
		{0, 6, 7, 8, 9, 10},
		{0, 11, 12, 13, 14, 15},
		{0, 16, 17, 18, 19, 20},
		{0, 0, 21, 22, 23, 24}
	};
	node *np = new node(val[0], 0);
	get_rank(np->val, fix[0]);
	/*rellenar_arreglo();
	bfs(np, fix);
	printf("Termine\n");
	printf("Nodos generados: %lu\n", counter);
	//np = new node(0x1f0f3f2fffffffff, 2);
	//printf("Val: %d\n", pdb_data[np->get_rank()]);
	write_bin("pdb_data_DEF.bin");*/
}
