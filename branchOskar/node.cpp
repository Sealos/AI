#include "node.h"
#include <ctime>
#include <cstdio>
#include <chrono>
#include <iostream>

unsigned int cant_nodos = 0;

#ifdef X_64

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

#else

unsigned int pos_mask[8] =
{
	0xF0000000,
	0x0F000000,
	0x00F00000,
	0x000F0000,
	0x0000F000,
	0x00000F00,
	0x000000F0,
	0x0000000F
};

#endif

//Sin revisar

#ifdef X_64
state::state(long unsigned int v)
{
    this->val = v;
}
#else
state::state(unsigned int v[])
{
    this->val[1] = v[1];
    this->val[2] = v[2];
}
#endif

state::state()
{
	//ctor
}

node::node(node *p, byte a, byte b)
{
	this->accion = a;
	this->acc_padre = b;
	this->g = p->g + 1;
	this->padre = p;
#ifdef X_64
	this->estado->val = p->estado->val;
#else
	this->estado->val[0] = p->estado->val[0];
	this->estado->val[1] = p->estado->val[1];
#endif

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
	set_value(0, this->pos_cero);
	set_value(val, p->pos_cero);

}


//Funciona
node::node(unsigned int val0, unsigned int val1, byte p_cero)
{
	this->pos_cero = p_cero;
	this->acc_padre = 0;
	this->accion = MOV_NULL;
	this->padre = NULL;
	this->g = 0;
#ifdef X_64
	long unsigned int temp = val0;
	temp = (temp << 32);
	this->estado->val = temp + val1;
#else
	this->estado->val[0] = val0;
	this->estado->val[1] = val1;
#endif
}


//Funciona
bool node::is_goal()
{
#ifdef X_64
	return this->estado->val == 0x0123456789ABCDEF;
#else
	return (this->estado->val[0] == 0x01234567 && this->estado->val[1] == 0x89ABCDEF);
#endif
}

//Funciona
std::list<byte> node::succ()
{
	std::list<byte> l_moves;
	switch(this->pos_cero)
	{
	case 0:
		l_moves.push_front(MOV_ABAJO);
		l_moves.push_front(MOV_DER);
		break;
	case 1:
	case 2:
		l_moves.push_front(MOV_ABAJO);
		l_moves.push_front(MOV_DER);
		l_moves.push_front(MOV_IZQ);
		break;
	case 3:
		l_moves.push_front(MOV_ABAJO);
		l_moves.push_front(MOV_IZQ);
		break;
	case 4:
	case 8:
		l_moves.push_front(MOV_ARRIBA);
		l_moves.push_front(MOV_ABAJO);
		l_moves.push_front(MOV_DER);
		break;
	case 5:
	case 6:
	case 9:
	case 10:
		l_moves.push_front(MOV_ARRIBA);
		l_moves.push_front(MOV_ABAJO);
		l_moves.push_front(MOV_DER);
		l_moves.push_front(MOV_IZQ);
		break;
	case 7:
	case 11:
		l_moves.push_front(MOV_ARRIBA);
		l_moves.push_front(MOV_ABAJO);
		l_moves.push_front(MOV_IZQ);
		break;
	case 12:
		l_moves.push_front(MOV_ARRIBA);
		l_moves.push_front(MOV_DER);
		break;
	case 13:
	case 14:
		l_moves.push_front(MOV_ARRIBA);
		l_moves.push_front(MOV_DER);
		l_moves.push_front(MOV_IZQ);
		break;
	case 15:
		l_moves.push_front(MOV_ARRIBA);
		l_moves.push_front(MOV_IZQ);
		break;
	}

	return l_moves;
}

byte node::inv(byte a)
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
	if (inv(a) == this->acc_padre)
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

//Funciona
int node::get_value(int n)
{
#ifdef X_64
	long unsigned int val;
	val = this->estado->val & pos_mask[n];
	int value = val >> ((15 - n) * 4);
	return value;
#else
	unsigned int val;
	if (n > 7)
		val = this->estado->val[1];
	else
		val = this->estado->val[0];
	n = n % 8;
	val = (val & pos_mask[n]);
	int value;
	if (n > 7)
		value = val >> ((15 - n)* 4);
	else
		value = val >> ((7 - n)* 4);
	return value;
#endif
}

//Funciona
void node::set_value(byte val, byte pos)
{
#ifdef X_64
	long unsigned int mask = ULONG_MAX - pos_mask[pos];
	long unsigned int sum_val = (this->estado->val & mask);
	if (val != 0)
	{
		long unsigned int new_val = val;
		new_val = new_val << ((15 - pos) * 4);
		this->estado->val = new_val + sum_val;
	}
	else
		this->estado->val = sum_val;

#else

	byte n = pos % 8;
	byte i = pos / 8;
	unsigned int mask = UINT_MAX - pos_mask[n];
	this->estado->val[i] = this->estado->val[i] & mask;
	if (val != 0)
	{
		unsigned int new_val = val;
		new_val = new_val << ((7 - n) * 4);
		this->estado->val[i] += new_val;
	}

#endif
}

//Sin revisar
std::list<byte> node::extract_solution()
{
	std::list<byte> path;
	node *n = this;
	path.push_front(n->padre->accion);
	while (n->acc_padre != 0)
	{
        n = n->padre;
		path.push_front(n->accion);
	}


	return path;
}


void node::print()
{
	for (int i = 0; i < 16; ++i)
	{
		printf("%d ", this->get_value(i));
	}
	printf("\n");
}

int node::hash()
{
#ifdef X_64
		int val1 = (this->estado->val & 0xFFFFFFFF00000000) >> 32;
		int val2 = (this->estado->val & 0x00000000FFFFFFFF);
		return val1 ^ val2;
#else
		printf("n.val : %x %x", this->estado->val[0], this->estado->val[1]);
		return (this->estado->val[0] ^ this->estado->val[1]);
#endif
}
