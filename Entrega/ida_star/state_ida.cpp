#include "state_ida.h"
#include <ctime>
#include <cstdio>
#include <chrono>
#include <iostream>

long unsigned int ida_mask[16] =
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

//Funciona
inline byte get_value(long unsigned int val0, int n)
{
	long unsigned int val;
	val = val0 & ida_mask[n];
	byte value = val >> ((15 - n) * 4);
	return value;
}

state_ida::state_ida(long unsigned int val, byte p_cero, int (*h)(unsigned char *))
{
	for (int i = 0; i < 16; ++i)
	{
		this->val[i] = get_value(val, i);
	}
	this->pos_cero = p_cero;
	this->closed = false;
	this->heur = h(this->val);
	this->dist = 0;
}

bool state_ida::valid_action(byte a)
{
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

bool state_ida::is_goal()
{
	for (int i = 0; i < 16; ++i)
	{
		if (this->val[i] != i)
			return false;
	}
	return true;
}

void state_ida::apply_action(byte a, int (*h)(unsigned char *))
{
	byte pos_cero = this->pos_cero;
	switch (a)
	{
	case MOV_ARRIBA:
		this->pos_cero = pos_cero - 4;
		break;
	case MOV_ABAJO:
		this->pos_cero = pos_cero + 4;
		break;
	case MOV_DER:
		this->pos_cero = pos_cero + 1;
		break;
	case MOV_IZQ:
		this->pos_cero = pos_cero - 1;
		break;
	case MOV_NULL:
		this->pos_cero = pos_cero;
		return;
	}

	int r_val = this->val[this->pos_cero];
	this->val[this->pos_cero] = 0;
	this->val[pos_cero] = r_val;
}
