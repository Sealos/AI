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
	byte heur;
	bool closed;
	long unsigned int val;
	byte dist;

public:

	state(long unsigned int val, byte p_cero, int (*h)(long unsigned int));
	state(long unsigned int val, byte pos_cero, byte a, int (*h)(long unsigned int));
	void set_value(byte val, byte pos);
	inline byte get_value(int n);
	bool valid_action(byte a);
	void apply_action(byte a, int (*h)(long unsigned int));
    bool operator==(const state &s) const { return val==s.val; }
    void operator=(const state &s) { val=s.val; heur=s.heur; closed=s.closed; dist=s.dist; pos_cero=s.pos_cero; }
    size_t hash() const {
        long unsigned int temp = val & ULONG_MAX;
        return temp;
    }
};

struct hash_state
{
    size_t operator()(const state *s) const {
        return s->hash();
    }
};

#endif /* STATE_H */
