/**
 * Proyecto 2: Othello
 * 
 * Inteligencia Artificial (CI5437)
 * 
 * Author:
 * 	 Stefano De Colli	09-10203 	
 *   Oskar González		09-10351
 *   Karen Troiano		09-10855
 */

#include "funciones.h"


int miniMax(state_t s, int depth){
	if (s.terminal() || depth == 0)
		return s.value()
	vector<int> succ = s.get_succ(true);
	
}

