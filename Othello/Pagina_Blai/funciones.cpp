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

int miniMaxAB(state_t s, int depth, int alpha,int betha,  bool max){
	if (s.terminal() || depth == 0)
		return s.value();

	if (max) {
		std::vector<int> succ = s.get_succ(false);
		if(succ.empty()){
			return miniMaxAB(s, depth - 1,alpha, betha, false);
		} else {
			for(int i = 0; i < succ.size(); ++i) {
				state_t new_s = s.move(false, succ[i]);
				alpha = std::max(alpha, miniMaxAB(new_s, depth - 1,alpha, betha, false));
				if (betha <= alpha)
					break;
			}
			return alpha;
		}
	} else {
		std::vector<int> succ = s.get_succ(true);
		if(succ.empty()){
			return miniMaxAB(s, depth - 1,alpha, betha, true);
		} else {
			for(int i = 0; i < succ.size(); ++i) {
				state_t new_s = s.move(true, succ[i]);
				betha = std::min(betha, miniMaxAB(new_s, depth - 1,alpha, betha, true));
				if (betha <= alpha)
					break;
			}
			return betha;
		}
	}

	return 0;
}

int negamax(state_t s, int depth, bool color){
    int seed = color? 1 : -1;
    if (s.terminal() || depth==0)
        return seed*s.value(color);

    int bestValue = _INF;
    std::vector<int> succ = s.getsucc(!color);
    if (succ.empty()){
        return seed*negamax(s,depth-1,!color);
    } else {
        for (int i = 0; i < succ.size(); ++i) {
            state_t new_s = s.move(!color,succ[i]);
            bestValue = -std::max(bestValue,-negamax(new_s,deph-1,!color))
        }
        return bestValue;
    }
    return 0;
}

int negamaxAB(state_t s, int depth,int alpha, int betha, bool color){

	if (s.terminal() || depth == 0)
		return s.value();

	int bestValue = alpha;
	int value;
	std::vector<int> succ = s.get_succ(color);

	if(succ.empty()){
			return -negamaxAB(s, depth - 1, -alpha, -betha, !color);
	} else {

		for(int i = 0; i < succ.size(); ++i) {
			state_t new_s = s.move(color, succ[i]);
			value = -negamaxAB(new_s, depth - 1,-betha, -bestValue, !color);
			if (value > bestValue)
				bestValue = value;
			if (bestValue >= betha)
				return bestValue;
		}
	}

	return bestValue;
}

int negaScout(state_t s, int depth,int alpha, int betha, bool color){

	if (s.terminal() || depth == 0)
		return s.value();

	int bestValueM = _INF;
	int bestValueN = betha;
	int value, maxi;
	std::vector<int> succ = s.get_succ(color);

	for(int i = 0; i < succ.size(); ++i) {
		state_t new_s = s.move(color, succ[i]);
		maxi = std::max(alpha,bestValueM);
		value = -negaScout(new_s, depth - 1, -bestValueN, -maxi, !color);

		if (value > bestValueM) {
			if ( bestValueN == betha || depth < 3 || value >= betha) {
				bestValueM = value;
			} else {
				m = -negaScout(new_s, depth - 1, -betha, -value, !color);
			}
		}

		if (bestValueN => betha)
			return bestValueM;

		bestValueN = maxi + 1;
	}

	return bestValueM;
}

