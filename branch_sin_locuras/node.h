// Nodo de 15 puzzle
#include "state.h"

#ifndef NODE_H
#define NODE_H

#define MOV_NULL	0
#define MOV_ARRIBA	1
#define MOV_ABAJO	2
#define MOV_DER		3
#define MOV_IZQ		4

typedef unsigned char byte;


/***
 * La información que se guarda en un
 * nodo n contiene:
 *	1. state(n) = estado representado
 * 		por n
 *	2. parent(n) = apunta al nodo i
 *		 padre de n
 * 	3. action(n) = operador que lleva
 * 		state(parent(n)) en state(n)
 * 	4. g(n) = costo de llegar a n desde
 * 		la raíz del arbol de busqueda
*/

class node
{
public:
	byte accion;
	node *padre;
	state *stt;
	int g;

public:
	node(node *p, byte a, int (*h)(long unsigned int));
	node(long unsigned int val, byte p_cero, int (*h)(long unsigned int));
	bool is_goal();
	bool valid_action(byte a);
	int get_value(int n);
	void set_value(byte val, byte pos);
	void print();

};

#endif /* NODE_H */
