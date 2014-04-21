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
	 * - SIN REVISAR -
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
	 * - FUNCIONA -
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
	node(unsigned int val0, unsigned int val1, unsigned char p_cero);


	/***
	 * - FUNCIONA -
	 * Chequea si es un estado objetivo
	 */
	bool is_goal();

	/***
	 * - FUNCIONA -
	 * Genera una lista con los sucesores
	 * del estado s y las acciones
	 * correspondientes
	 */
	std::list<unsigned char> succ();

	/***
	 * - FUNCIONA -
	 * Obtiene el valor de la ficha de la posicion n
	 */
	int get_value(int n);

	/***
	 * - FUNCIONA -
	 * Coloca el valor val de la posicion pos
	 */
	void set_value(unsigned char val, unsigned char pos);

	/***
	 * - SIN REVISAR -
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

	void print();

};

/*namespace std
{
	template <>
		class hash<node>
		{
		public :
			size_t operator()(const node &n ) const
			{
				#ifdef X_64
						int val1 = (n.val & 0xFFFFFFFF00000000) >> 32;
						int val2 = (n.val & 0x00000000FFFFFFFF);
						return val1 ^ val2;
				#else
						return (n.val[0] ^ n.val[1]);
				#endif
			}
		};
};
*/

#endif /* NODE_H */
