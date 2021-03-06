#include "node.h"

//int cant_nodos = 0;

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

using namespace std;

unordered_set<state*, hash_state> mapa; // Cambiar a set

node::node(node *p, byte a, int (*h)(long unsigned int))
{
	this->accion = a;
	this->g = p->g + 1;
	this->padre = p;

	long unsigned int v = p->stt->val;
	state *s = new state(v, p->stt->pos_cero, a, h);

	if (mapa.find(s)==mapa.end()) { //Si s no esta en el conjunto mapa
        mapa.insert(s);
	}
	this->stt = s;
	//++cant_nodos;
}

//Funciona
node::node(long unsigned int val, byte p_cero, int (*h)(long unsigned int))
{
	this->accion = MOV_NULL;
	this->padre = NULL;
	this->g = 0;

	state *s = new state(val, p_cero, h);
	mapa.insert(s);
	this->stt = s;
	//++cant_nodos;
}


//Funciona
bool node::is_goal()
{
	return (this->stt->val == 0x0123456789ABCDEF);
}

bool node::valid_action(byte a)
{
	switch(this->stt->pos_cero)
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

//Funciona
int node::get_value(int n)
{
	long unsigned int val;
	val = this->stt->val & pos_mask[n];
	int value = val >> ((15 - n) * 4);
	return value;
}

//Funciona
void node::set_value(byte val, byte pos)
{
	long unsigned int mask = ULONG_MAX - pos_mask[pos];
	long unsigned int sum_val = (this->stt->val & mask);
	if (val != 0)
	{
		long unsigned int new_val = val;
		new_val = new_val << ((15 - pos) * 4);
		this->stt->val = new_val + sum_val;
	}
	else
		this->stt->val = sum_val;
}

void node::print()
{
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
	printf("\n\n");
}

void node::print_l()
{
	for (int i = 0; i < 4; ++i)
	{
		printf("%d ", this->get_value(i));
	}
	for (int i = 4; i < 8; ++i)
	{
		printf("%d ", this->get_value(i));
	}
	for (int i = 8; i < 12; ++i)
	{
		printf("%d ", this->get_value(i));
	}
	for (int i = 12; i < 16; ++i)
	{
		printf("%d ", this->get_value(i));
	}
	printf(": ");
}
