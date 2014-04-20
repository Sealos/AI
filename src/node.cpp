#include "node.h"

#ifdef X_64

unsigned long int pos_mask[16] =
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
node::node(node *p, unsigned char a)
{
	this->padre = p;
	this->accion = a;
	this->g = p->g + 1;
	//swap
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
	}

	int val = p->get_value(this->pos_cero);
#ifdef X_64
	this->val = p->val;
#else
	this->val[0] = p->val[0];
	this->val[1] = p->val[1];
#endif
	set_value(0, this->pos_cero);
	set_value(val, p->pos_cero);

}

//Funciona
node::node(unsigned int val0, unsigned int val1, unsigned char p_cero)
{
	this->pos_cero = p_cero;
	this->padre = NULL;
	this->accion = MOV_NULL;
	this->g = 0;
#ifdef X_64
	unsigned long int temp = val0;
	temp = (temp << 32);
	this->val = temp + val1;
#else
	this->val[0] = val0;
	this->val[1] = val1;
#endif
}

//Funciona
bool node::is_goal()
{
#ifdef X_64
	return this->val == 0x0123456789ABCDEF;
#else
	return (this->val[0] == 0x01234567 && this->val[1] == 0x89ABCDEF);
#endif
}

//Funciona
std::list<unsigned char> node::succ()
{
	std::list<unsigned char> l_moves;
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

//Funciona
int node::get_value(int n)
{
#ifdef X_64
	unsigned long int val;
	val = this->val & pos_mask[n];
	int value = val >> ((15 - n) * 4);
	return value;
#else
	unsigned int val;
	if (n > 7)
		val = this->val[1];
	else
		val = this->val[0];
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
void node::set_value(unsigned char val, unsigned char pos)
{
#ifdef X_64
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

#else

	unsigned char n = pos % 8;
	unsigned char i = pos / 8;
	unsigned int mask = UINT_MAX - pos_mask[n];
	this->val[i] = this->val[i] & mask;
	if (val != 0)
	{
		unsigned int new_val = val;
		new_val = new_val << ((7 - n) * 4);
		this->val[i] += new_val;
	}

#endif
}

//Sin revisar
std::list<unsigned char> node::extract_solution()
{
	std::list<unsigned char> path;
	node *n = this;
	path.push_front(n->accion);
	while (n->padre != NULL)
	{
        n = n->padre;
		path.push_front(n->accion);
	}


	return path;
}

bool compare_node::operator()(node* n1, node* n2)
{
	return false;
}

void node::print()
{
	for (int i = 0; i < 16; ++i)
	{
		printf("%d ", this->get_value(i));
	}
	printf("\n");
}
