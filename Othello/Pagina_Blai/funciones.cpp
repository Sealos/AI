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
				hash_table_t::const_iterator it = tabla.find(new_s);
				if (it == tabla.end())
				{
					val = miniMax(new_s, depth - 1, false);
					tabla.insert(std::make_pair(new_s, val));
				}
				else
					val = it->second;
				
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
				hash_table_t::const_iterator it = tabla.find(new_s);
				if (it == tabla.end())
				{
					val = miniMax(new_s, depth - 1, true);
					tabla.insert(std::make_pair(new_s, val));
				}
				else
					val = it->second;
				
				bestValue = std::min(bestValue, val);
			}
			return bestValue;
		}
	}

	return 0;
}

int miniMaxAB(state_t s, int depth, int alpha, int betha,  bool max)
{
	if(s.terminal() || depth == 0)
		return s.value();

	if(max)
	{
		std::vector<int> succ = s.get_succ(true);
		if(succ.empty())
			return miniMaxAB(s, depth - 1, alpha, betha, false);
		else
		{
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(true, succ[i]);
				
				alpha = std::max(alpha, miniMaxAB(new_s, depth - 1, alpha, betha, false));
				if(betha <= alpha)
					break;
			}
			return alpha;
		}
	}
	else
	{
		std::vector<int> succ = s.get_succ(false);
		if(succ.empty())
			return miniMaxAB(s, depth - 1, alpha, betha, true);
		else
		{
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(false, succ[i]);
				betha = std::min(betha, miniMaxAB(new_s, depth - 1, alpha, betha, true));
				if(betha <= alpha)
					break;
			}
			return betha;
		}
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
	if(succ.empty())
		return -negamax(s, depth - 1, !color);
	else
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);
			value = -negamax(new_s, depth - 1, !color);
			bestValue = std::max(bestValue, value);
		}
		return bestValue;
	}
	return bestValue;
}

int negamaxAB(state_t s, int depth, int alpha, int betha, bool color)
{

	int seed = color ? 1 : -1;
	
	if(s.terminal() || depth == 0)
		return seed * s.value();

	int bestValue = alpha;
	int value;
	std::vector<int> succ = s.get_succ(color);

	if(succ.empty()){
		value = -negamaxAB(s, depth - 1, -betha, -alpha, !color);
		//std::cout << "Paso: " << value << std::endl;
		return value;
		
		}
	else
	{

		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);
			value = -negamaxAB(new_s, depth - 1, -betha, -bestValue, !color);
			bestValue = std::max(bestValue, value);
			//std::cout << "Value: " << value << std::endl;
			//std::cout << "bestValue: " << bestValue << std::endl;
			//std::cout << "----------------" << std::endl;
			if(bestValue >= betha){
				break;
			}
		}

	}

	return bestValue;
}

int negaScout(state_t s, int depth, int alpha, int betha, bool color)
{

	int seed = color ? 1 : -1;

	if(s.terminal() || depth == 0)
		return seed * s.value();

	int bestValueM = _INF;
	int bestValueN = betha;
	int value, maxi;
	std::vector<int> succ = s.get_succ(color);
	if(succ.empty())
		return -negaScout(s, depth - 1, -betha, -alpha, !color);
	else
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);
			maxi = std::max(alpha, bestValueM);
			value = -negaScout(new_s, depth - 1, -bestValueN, -maxi, !color);

			if(value > bestValueM)
			{
				if(bestValueN == betha || depth < 3 || value >= betha)
					bestValueM = value;
				else
					bestValueM = -negaScout(new_s, depth - 1, -betha, -value, !color);
			}

			if(bestValueN >= betha)
				return bestValueM;

			bestValueN = maxi + 1;
		}
	}

	return bestValueM;
}

