// Nodo de 15 puzzle
#include <list>
#include <stdio.h>
#include <climits>

#ifndef NODE_H
#define NODE_H

#define MOV_NULL	0
#define MOV_ARRIBA	1
#define MOV_ABAJO	2
#define MOV_DER		3
#define MOV_IZQ		4

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
	unsigned char pos_cero;
	node *padre;
	unsigned char accion;
	int g;

#ifdef X_64
	unsigned long int val;
#else
	unsigned int val[2];
#endif

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
	node(node *p, unsigned char a);

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
	node(unsigned int val0, unsigned int val1);

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
	std::list<unsigned char> succ();

	/***
	 * Obtiene el valor de la ficha de la posicion n
	 */
	int get_value(int n);

	void set_value(unsigned char val, unsigned char pos);

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
	std::list<unsigned char> extract_solution();
};

#endif /* NODE_H */
