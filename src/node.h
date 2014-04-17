// Nodo de 15 puzzle
#include <stdio.h>
#include <cstdlib>
#include "define.h"
#include <list>

#ifndef NODE_H
#define NODE_H

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
	int8_t pos_cero;
	node *padre;

#ifdef X_64
	unsigned long int val;
#else
	unsigned int val[2];
#endif

public:
	/***
	 * Genera una estructura de
	 * datos que representa el estado i
	*/
	//rep init();

	/***
	 * Chequea si es un estado objetivo
	 */
	bool is_goal();

	/***
	 * Genera una lista con los sucesores
	 * del estado s y las acciones
	 * correspondientes
	 */
	std::list<int> succ();

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
	//node make_root(rep);

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
	//node make_node(n,a,s);

	/***
	 * Construye el unico camino
	 * de la raíz a al nodo n:
	 *
	 * 	path :=new lista
	 * 	while parent(n)! = null do
	 * 		path.push − front(action(n))
	 *		 n := parent(n)
	 * 	end while
	 * 	return path
	 */
	//extract_solution(n);
};

#endif /* NODE_H */
