// Nodo de 15 puzzle
#include "node.h"

node::node(node *padre, int accion)
{
	this->padre = padre;
}

node::node(unsigned int val0, unsigned int val1)
{
	this->padre = nullptr;
#ifdef X_64
	unsigned long int temp = (val0 << 32);
	this->val = temp + val1;
#else
	this->val[0] = val0;
	this->val[1] = val1;
#endif
}

bool node::is_goal()
{
#ifdef X_64
	return this->val == 0x123456789ABCDEF0;
#else
	return (this->val[0] == 0x12345678 && this->val[1] == 0x9ABCDEF0);
#endif
}

std::list<int> node::succ()
{
	std::list<int> l_moves;
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
