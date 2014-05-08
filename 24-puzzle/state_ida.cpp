#include "state_ida.h"
#include <ctime>
#include <cstdio>
#include <chrono>
#include <iostream>

state_ida::state_ida(byte *rep, byte p_cero, int (*h)(unsigned char *))
{
	for (int i = 0; i < 16; ++i)
		this->val[i] = rep[i];

	this->pos_cero = p_cero;
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

bool state_ida::is_goal()
{
	for (int i = 0; i < 25; ++i)
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
		this->pos_cero = pos_cero - 5;
		break;
	case MOV_ABAJO:
		this->pos_cero = pos_cero + 5;
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
