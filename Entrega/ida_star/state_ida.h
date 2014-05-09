// Nodo de 15 puzzle
#include <list>
#include <stdio.h>
#include <climits>
#include <functional>
#include <cstdio>
#include <chrono>
#include <iostream>
#include <unordered_map>

#ifndef STATE_IDA_H
#define STATE_IDA_H

#define MOV_NULL	0
#define MOV_ARRIBA	1
#define MOV_ABAJO	2
#define MOV_DER		3
#define MOV_IZQ		4

typedef unsigned char byte;


class state_ida
{
public:
	byte pos_cero;
	byte heur;
	bool closed;
	unsigned char val[16];
	byte dist;

public:

	state_ida(long unsigned int val, byte p_cero, int (*h)(unsigned char *));
	bool valid_action(byte a);
	void apply_action(byte a, int (*h)(unsigned char *));
	bool is_goal();
};

#endif /* STATE_H */
