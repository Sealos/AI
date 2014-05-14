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

int miniMax(state_t s, int depth, bool max){
	if (s.terminal() || depth == 0)
		return s.value();
	
	if (max) {
		std::vector<int> succ = s.get_succ(false);
		if(succ.empty()){
			return miniMax(s, depth - 1, false);
		} else {
			int bestValue = _INF;
			for(int i = 0; i < succ.size(); ++i) {
				state_t new_s = s.move(false, succ[i]);
				bestValue = std::max(bestValue, miniMax(new_s, depth - 1, false));
			}
			return bestValue;
		}
	} else {
		std::vector<int> succ = s.get_succ(true);
		if(succ.empty()){
			return miniMax(s, depth - 1, true);
		} else {
			int bestValue = INF;
			for(int i = 0; i < succ.size(); ++i) {
				state_t new_s = s.move(true, succ[i]);
				bestValue = std::min(bestValue, miniMax(new_s, depth - 1, true));
			}
			return bestValue;
		}
	}
	
	return 0;
}

