// Nodo de 15 puzzle
#include <stdio.h>
#include <cstdlib>

#ifndef NODE_H
#define NODE_H

#ifdef X_64

#define POS_0	0xF000000000000000
#define POS_1	0x0F00000000000000
#define POS_2	0x00F0000000000000
#define POS_3	0x000F000000000000
#define POS_4	0x0000F00000000000
#define POS_5	0x00000F0000000000
#define POS_6	0x000000F000000000
#define POS_7	0x0000000F00000000
#define POS_8	0x00000000F0000000
#define POS_9	0x000000000F000000
#define POS_10	0x0000000000F00000
#define POS_11	0x00000000000F0000
#define POS_12	0x000000000000F000
#define POS_13	0x0000000000000F00
#define POS_14	0x00000000000000F0
#define POS_15	0x000000000000000F

#else

#define POS_0	0xF0000000
#define POS_1	0x0F000000
#define POS_2	0x00F00000
#define POS_3	0x000F0000
#define POS_4	0x0000F000
#define POS_5	0x00000F00
#define POS_6	0x000000F0
#define POS_7	0x0000000F
#define POS_8	0xF0000000
#define POS_9	0x0F000000
#define POS_10	0x00F00000
#define POS_11	0x000F0000
#define POS_12	0x0000F000
#define POS_13	0x00000F00
#define POS_14	0x000000F0
#define POS_15	0x0000000F

#endif


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
private:
	int8_t pos_cero;
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
	//list succ(s);

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
