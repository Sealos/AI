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
	/***
	 * Construye un nodo que
	 * representa al estado s que
	 * es hijo del estado n a traves
	 * de la accion a:
	 *
	 * 	n :=new nodo
	 * 	state(n ) := s
	 * 	parent(n ) := n
	 * 	action(n ) := a
	 * 	g(n ) := g(n) + cost(state(n), a)
	 * 	return n
	 */
	node(node *p, byte a);

	/***
	 * Construye la raíz del arbol de
	 * búsqueda:
	 *
	 * 	n :=new nodo
	 * 	state(n) := s
	 * 	parent(n) := null
	 * 	action(n) := null
	 * 	g(n) := null
	 * 	return n
	 */
	node(long unsigned int val, byte p_cero);

	/***
	 * - FUNCIONA -
	 * Chequea si es un estado objetivo
	 */
	bool is_goal();

	bool valid_action(byte a);

	/***
	 * - FUNCIONA -
	 * Obtiene el valor de la ficha de la posicion n
	 */
	int get_value(int n);

	/***
	 * - FUNCIONA -
	 * Coloca el valor val de la posicion pos
	 */
	void set_value(byte val, byte pos);

	void print();
	

};

#endif /* NODE_H */
