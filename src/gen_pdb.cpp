#include "gen_pdb.h"

#define  EQUIS	0x1

#define MOV_NULL	0
#define MOV_ARRIBA	1
#define MOV_ABAJO	2
#define MOV_DER		3
#define MOV_IZQ		4

#define MAX_VALUE	5765760

long unsigned int pos_mask[16] =
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

unsigned char pdb_data[MAX_VALUE];

long unsigned int counter = 0;
std::unordered_set<unsigned long int> closed;

std::vector<unsigned long int> factorial(16,1);

node::node(node *p, unsigned char a)
{
	this->padre = p;
	this->accion = a;
	this->val = p->val;

	switch (a)
	{
	case MOV_ARRIBA:
		this->pos_cero = p->pos_cero - 4;
		break;
	case MOV_ABAJO:
		this->pos_cero = p->pos_cero + 4;
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

	int val = p->get_value(this->pos_cero);
	if (val != EQUIS)
		this->g = p->g + 1;
	set_value(0, this->pos_cero);
	set_value(val, p->pos_cero);
}

node::node(unsigned long int val0, unsigned char p_cero)
{
	this->pos_cero = p_cero;
	this->padre = NULL;
	this->accion = MOV_NULL;
	this->g = 0;
	this->val = val0;
}

int node::get_value(int n)
{
	unsigned long int val;
	val = this->val & pos_mask[n];
	int value = val >> ((15 - n) * 4);
	return value;
}

void node::set_value(unsigned char val, unsigned char pos)
{
	unsigned long int mask = ULONG_MAX - pos_mask[pos];
	unsigned long int sum_val = (this->val & mask);
	if (val != 0)
	{
		unsigned long int new_val = val;
		new_val = new_val << ((15 - pos) * 4);
		this->val = new_val + sum_val;
	}
	else
		this->val = sum_val;
}

unsigned long int node::get_rank()
{
	std::vector<int> freq(16);
	unsigned long int den = 1;
	unsigned long int ret = 0;
	for(int i = 15; i >= 0; --i)
	{
		int si = this->get_value(i);
		freq[si]++;
		den *= freq[si];
		for (int c = 0; c < si; ++c) 
			if(freq[c] > 0) 
				ret += factorial[15-i] / (den / freq[c]);
	}
	return ret + 1;
}

bool node::valid_action(unsigned char a)
{
	unsigned char b = this->padre == NULL ? MOV_NULL : this->padre->accion;
	if (a == b)
		return false;

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
		switch(a)
		{
		case MOV_ARRIBA:
			return false;
		default:
			return true;
		}
	case 3:
		switch(a)
		{
		case MOV_ABAJO:
		case MOV_IZQ:
			return true;
		default:
			return false;
		}
	case 4:
	case 8:
		switch(a)
		{
		case MOV_IZQ:
			return false;
		default:
			return true;
		}
	case 5:
	case 6:
	case 9:
	case 10:
		return true;
	case 7:
	case 11:
		switch(a)
		{
		case MOV_DER:
			return false;
		default:
			return true;
		}
	case 12:
		switch(a)
		{
		case MOV_ARRIBA:
		case MOV_DER:
			return true;
		default:
			return false;
		}
	case 13:
	case 14:
		switch(a)
		{
		case MOV_ABAJO:
			return false;
		default:
			return true;
		}
	case 15:
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
	for (int i = 0; i < 4; ++i)
	{
		printf("%2d ", this->get_value(i));
	}
	printf("\n");
	for (int i = 4; i < 8; ++i)
	{
		printf("%2d ", this->get_value(i));
	}
	printf("\n");
	for (int i = 8; i < 12; ++i)
	{
		printf("%2d ", this->get_value(i));
	}
	printf("\n");
	for (int i = 12; i < 16; ++i)
	{
		printf("%2d ", this->get_value(i));
	}
	printf("\n--\n");
}

void write_bin(std::string fname)
{
	std::ofstream myfile;
	myfile.open (fname);
	myfile.write((const char*)&pdb_data, MAX_VALUE);
}

void bfs(node *p)
{
	std::queue<node *> Q;
	Q.push(p);
	while(!Q.empty())
	{
		node *actual = Q.front();
		Q.pop();
		if (counter == MAX_VALUE)
		{
			return;
		}

		if (closed.find(actual->val) == closed.end())
		{
			++counter;
			closed.insert(actual->val);
			pdb_data[actual->get_rank()] = actual->g;
			for (unsigned char i = 1; i <= 4; ++i)
			{
				if (actual->valid_action(i))
				{
					p = new node(actual, i);
					Q.push(p);
				}

			}
		}
	}
}

void rellenar_arreglo()
{
	for (unsigned long int i = 0; i < MAX_VALUE; ++i)
	{
		pdb_data[i] = 0xFF;
	}
}

int main(int argc, const char* argv[])
{
	for(int i = 1; i <= 15; ++i)
		factorial[i] = i * factorial[i-1];
	unsigned long int val = 0x0111111111BCDEF;
	node *np = new node(val, 0);
	rellenar_arreglo();
	bfs(np);
	printf("Termine\n");
	printf("Nodos generados: %lu\n", counter);
	write_bin("pdb_data_BCDEF.bin");
	/*for (unsigned long int i = 0; i < MAX_VALUE; ++i)
	{
		printf("Rank %lu, Val %d\n", i, pdb_data[i]);
	}*/
}