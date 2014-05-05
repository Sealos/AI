// Nodo de 15 puzzle
#include <list>
#include <stdio.h>
#include <climits>
#include <functional>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <unordered_map>

#ifndef STATE_H
#define STATE_H

#define MOV_NULL	0
#define MOV_ARRIBA	1
#define MOV_ABAJO	2
#define MOV_DER		3
#define MOV_IZQ		4

typedef unsigned char byte;


class state
{
public:
	byte pos_cero;
	bool closed; 
	long unsigned int val;

public:
	
	state(long unsigned int val, byte p_cero);
	state(long unsigned int val, byte pos_cero, byte a);
	void set_value(byte val, byte pos);
	inline byte get_value(int n);
};

#endif /* STATE_H */
