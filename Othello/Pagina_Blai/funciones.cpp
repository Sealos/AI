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
#include <algorithm>

hash_table_t tabla;

int miniMax(state_t s, int depth, bool max)
{
	if(s.terminal() || depth == 0)
		return s.value();

	if(max)
	{
		std::vector<int> succ = s.get_succ(true);
		if(succ.empty())
			return miniMax(s, depth - 1, false);
		else
		{
			int bestValue = _INF;
			int val;
			for(int i = 0; i < succ.size(); ++i)
			{
 				state_t new_s = s.move(true, succ[i]);
// 				hash_table_t::const_iterator it = tabla.find(new_s);
// 				if (it == tabla.end())
// 				{
					val = miniMax(new_s, depth - 1, false);
// 					tabla.insert(std::make_pair(new_s, std::abs(val)));
// 				}
// 				else
// 					val = it->second;

				bestValue = std::max(bestValue, val);
			}
			return bestValue;
		}
	}
	else
	{
		std::vector<int> succ = s.get_succ(false);
		if(succ.empty())
			return miniMax(s, depth - 1, true);
		else
		{
			int bestValue = INF;
			int val;
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(false, succ[i]);
// 				hash_table_t::const_iterator it = tabla.find(new_s);
// 				if (it == tabla.end())
// 				{
					val = miniMax(new_s, depth - 1, true);
// 					tabla.insert(std::make_pair(new_s, std::abs(val)));
// 				}
// 				else
// 					val = -it->second;

				bestValue = std::min(bestValue, val);
			}
			return bestValue;
		}
	}

	return 0;
}

int miniMaxAB(state_t s, int depth, int alpha, int betha,  bool jugador)
{
	if(s.terminal())
		return s.value();

	std::vector<int> succ = s.get_succ(jugador);

	if(succ.size() <= 0){
			return miniMaxAB(s, depth - 1, alpha, betha, !jugador);
	}

	if(jugador)//MAX
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(jugador, succ[i]);
			int val;

//                 hash_table_t::const_iterator it = tabla.find(new_s);
// 				if (it == tabla.end())
// 				{
				val = miniMaxAB(new_s, depth - 1, alpha, betha, !jugador);
				//if(depth == 16) std::cout << "Max: i=" << i << ", val=" << val << std::endl;
// 					tabla.insert(std::make_pair(new_s, std::abs(val)));
// 				}
// 				else{
// 					val = it->second;
// 				}

			alpha = MAX(alpha, val);

			if(betha <= alpha)
				break;
		}
		return alpha;

	}
	else //MIN
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(jugador, succ[i]);
			int val;

// 				hash_table_t::const_iterator it = tabla.find(new_s);
// 				if (it == tabla.end())
// 				{
				val = miniMaxAB(new_s, depth - 1, alpha, betha, !jugador);
				//if(depth == 15) std::cout << "Min: i=" << i << ", val=" << val << std::endl;

				// 					tabla.insert(std::make_pair(new_s, std::abs(val)));
// 				}
// 				else{
// 					val = -it->second;
// 				}

			betha = MIN(betha, val);

			if(betha <= alpha)
				break;
		}

		return betha;
	}

	return 0;
}

int negamax(state_t s, int depth, bool color)
{
	int seed = color ? 1 : -1;

	if(s.terminal() || depth == 0)
		return seed * s.value();


	int bestValue = _INF;
	int value;
	std::vector<int> succ = s.get_succ(color);

	if(succ.empty()) {
		return -negamax(s, depth - 1, !color);
	} else
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);

// 			hash_table_t::const_iterator it = tabla.find(new_s);
// 			if (it == tabla.end())
// 			{
				value = -negamax(new_s, depth - 1, !color);
// 				tabla.insert(std::make_pair(new_s, std::abs(value)));
// 			}
// 			else {
// 				value = seed * it->second;
// 			}

			bestValue = std::max(bestValue, value);
		}
	}
	return bestValue;
}

int negamaxAB(state_t s, int depth, int alpha, int betha, bool color)
{
	int seed = color ? 1 : -1;

	if(s.terminal())
		return seed * s.value();

	int bestValue = alpha;
	int value;
	std::vector<int> succ = s.get_succ(color);

	if(succ.size() <= 0){
		return  -negamaxAB(s, depth - 1, -betha, -alpha, !color);
	}
	else {

		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);

// 			hash_table_t::const_iterator it = tabla.find(new_s);
//  			if (it == tabla.end())
//  			{
 				value = -negamaxAB(new_s, depth - 1, -betha, -bestValue, !color);
/* */				tabla.insert(std::make_pair(new_s, std::abs(value)));
//  			}
//  			else {
//  				value = seed * it->second;
//  		}
//
			if (value > bestValue) {
				bestValue = value;
			}
			if (bestValue >= betha) {
				return bestValue;
			}
		}

	}

	return bestValue;
}

int scout(state_t s, int depth, bool color){
    if (s.terminal()/*|| depth==0*/)
        return s.value();
    std::vector<int> succ = s.get_succ(color);
	if(succ.size() <= 0){
			return scout(s, depth - 1, !color);
	} else {
	    state_t new_s = s.move(color, succ[0]);
	    int v = scout(new_s, depth-1, !color);
	    for(int i = 1; i < succ.size(); ++i){
            state_t new_s = s.move(color, succ[i]);
            std::greater<int> mayq;
            if (color && test(new_s, depth-1, v, !color, mayq))
                v = scout(new_s, depth-1, !color);
            std::less<int> menq;
            if (!color && test(new_s, depth-1, v, !color, menq))
                v = scout(new_s, depth-1, !color);
	    }
	    return v;
	}
	return 0;
}

template <typename Comparator>
bool test(state_t s, int depth, int v, bool color, Comparator comp){
    if (s.terminal()/* || depth==0*/)
        return comp(s.value(),v);
    std::vector<int> succ = s.get_succ(color);
	if(succ.size() <= 0){
			return test(s, depth - 1, v, !color, comp); //No estoy muy seguro de esta linea...
	} else {
	    for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);
			if (color && test(new_s,depth-1,v,!color,comp))
                return true;
            if (!color && !test(new_s,depth-1,v,!color,comp))
                return false;
		}
	}
    if (color)
        return false;
    return true;
}

int negaScout(state_t s, int depth, int alpha, int betha, bool color)
{

	int seed = color ? 1 : -1;

	if(s.terminal())
		return seed * s.value();

	int bestValueM = _INF;
	int bestValueN = betha;
	int value;

	std::vector<int> succ = s.get_succ(color);

	if(succ.size() <= 0){
		return -negaScout(s, depth - 1, -betha, -alpha, !color);
	}
	else
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);

			value = -negaScout(new_s, depth - 1, -bestValueN, -std::max(bestValueM, alpha), !color);

			if(value > bestValueM)
			{
				if((bestValueN == betha) || (depth < 3) || (value >= betha))
					bestValueM = value;
				else
					bestValueM = -negaScout(new_s, depth - 1, -betha, -value, !color);
			}

			if(bestValueM >= betha)
				return bestValueM;

			bestValueN = std::max(alpha, bestValueM) + 1;
		}
	}

	return bestValueM;
}

