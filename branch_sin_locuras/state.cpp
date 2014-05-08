#include "state.h"
#include <ctime>
#include <cstdio>
#include <chrono>
#include <iostream>

long unsigned int p_mask[16] =
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
inline byte state::get_value(int n)
{
	long unsigned int val;
	val = this->val & p_mask[n];
	byte value = val >> ((15 - n) * 4);
	return value;
}

//Funciona
void state::set_value(byte val, byte pos)
{
	long unsigned int mask = ULONG_MAX - p_mask[pos];
	long unsigned int sum_val = (this->val & mask);
	if (val != 0)
	{
		long unsigned int new_val = val;
		new_val = new_val << ((15 - pos) * 4);
		this->val = new_val + sum_val;
	}
	else
		this->val = sum_val;
}

state::state(long unsigned int val, byte p_cero, int (*h)(long unsigned int))
{
	this->pos_cero = p_cero;
	this->closed = false;
	this->heur = 0xFF;
	this->val = val;
	this->heur = h(val);
	this->dist = 0;
}

state::state(long unsigned int val, byte pos_cero, byte a, int (*h)(long unsigned int))
{

	this->val = val;
	this->closed = false;
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

	int r_val = this->get_value(this->pos_cero);
	set_value(0, this->pos_cero);
	set_value(r_val, pos_cero);
	this->heur = h(this->val);
	this->dist = 0;
}

bool state::valid_action(byte a)
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

void state::apply_action(byte a, int (*h)(long unsigned int))
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

	int r_val = this->get_value(this->pos_cero);
	set_value(0, this->pos_cero);
	set_value(r_val, pos_cero);
}

