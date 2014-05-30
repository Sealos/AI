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
hash_table_ tabla_ab;

int miniMax(state_t s, int depth, bool jugador)
{
	if(s.terminal())
		return s.value();

	if(jugador)
	{
		//MAX
		std::vector<int> succ = s.get_succ(jugador);
		if(succ.empty())
			return miniMax(s, depth - 1, !jugador);
		else
		{
			int bestValue = _INF;
			int val;
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(jugador, succ[i]);
				hash_table_t::const_iterator it = tabla.find(new_s);
				if(it == tabla.end())
				{
					val = miniMax(new_s, depth - 1, !jugador);
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
		//MIN
		std::vector<int> succ = s.get_succ(jugador);
		if(succ.empty())
			return miniMax(s, depth - 1, !jugador);
		else
		{
			int bestValue = INF;
			int val;
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(jugador, succ[i]);
				hash_table_t::const_iterator it = tabla.find(new_s);
				if(it == tabla.end())
				{
					val = miniMax(new_s, depth - 1, !jugador);
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

int miniMaxAB(state_t s, int depth, int alpha, int betha,  bool jugador)
{
	if(s.terminal())
		return s.value();

	std::vector<int> succ = s.get_succ(jugador);

	if(succ.size() <= 0)
		return miniMaxAB(s, depth - 1, alpha, betha, !jugador);

	if(jugador)//MAX
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(jugador, succ[i]);
			int val;

			hash_table_t::const_iterator it = tabla.find(new_s);

			if(it == tabla.end())
			{
				val = miniMaxAB(new_s, depth - 1, alpha, betha, !jugador);
				tabla.insert(std::make_pair(new_s, val));
			}
			else
				val = it->second;

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

			hash_table_t::const_iterator it = tabla.find(new_s);
			if(it == tabla.end())
			{
				val = miniMaxAB(new_s, depth - 1, alpha, betha, !jugador);
				tabla.insert(std::make_pair(new_s, val));
			}
			else
				val = it->second;

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

	if(s.terminal())
		return seed * s.value();

	int bestValue = _INF;
	int value;
	std::vector<int> succ = s.get_succ(color);

	if(succ.size() <= 0)
		return -negamax(s, depth - 1, !color);
	else
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);

			hash_table_t::const_iterator it = tabla.find(new_s);
			if(it == tabla.end())
			{
				value = -negamax(new_s, depth - 1, !color);
				tabla.insert(std::make_pair(new_s, value));
			}
			else
				value = it->second;

			bestValue = MAX(bestValue, value);
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

	if(succ.size() <= 0)
	{
// 		hash_table_t::const_iterator it = tabla.find(s);
// 		if(it == tabla.end())
// 		{
			value = -negamaxAB(s, depth - 1, -betha, -alpha, !color);
// 			tabla.insert(std::make_pair(s, value));
// 		}
// 		else
// 			value = it->second;
		return value;
	}
	else
	{

		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);

// 			hash_table_t::const_iterator it = tabla.find(new_s);
// 			if(it == tabla.end())
// 			{
				value = -negamaxAB(new_s, depth - 1, -betha, -bestValue, !color);
// 				tabla.insert(std::make_pair(new_s, value));
// 			}
// 			else
// 				value = it->second;

			if(value > bestValue)
				bestValue = value;
			if(bestValue >= betha)
				return bestValue;
		}

	}

	return bestValue;
}

bool MAYOR(int a, int b)
{
	return (a > b);
}

bool MENOR(int a, int b)
{
	return (a < b);
}

//template <typename Comparator>
bool test(state_t s, int depth, int v, bool color,  bool (*comp)(int, int))
{

	if(s.terminal())
		return comp(s.value(), v);

	std::vector<int> succ = s.get_succ(color);

	if(succ.size() <= 0)
	{
		return test(s, depth - 1, v, !color, comp); //No estoy muy seguro de esta linea...
	}
	else
	{

		if(comp == MAYOR)
		{
			if(color)
			{
				for(int i = 0; i < succ.size(); ++i)
				{
					state_t new_s = s.move(color, succ[i]);

					if((test(new_s, depth - 1, v, !color, comp) == true))
						return true;

				}
				return false;
			}
			else
			{

				for(int i = 0; i < succ.size(); ++i)
				{
					state_t new_s = s.move(color, succ[i]);

					if((test(new_s, depth - 1, v, !color, comp) == false))
						return false;

				}
				return true;
			}
		}
		else
		{

			if(color)
			{
				for(int i = 0; i < succ.size(); ++i)
				{
					state_t new_s = s.move(color, succ[i]);

					if((test(new_s, depth - 1, v, !color, comp) == false))
						return false;

				}
				return true;
			}
			else
			{

				for(int i = 0; i < succ.size(); ++i)
				{
					state_t new_s = s.move(color, succ[i]);

					if((test(new_s, depth - 1, v, !color, comp) == true))
						return true;

				}
				return false;
			}

		}
	}

}

int scout(state_t s, int depth, bool color)
{

	if(s.terminal())
		return s.value();

	std::vector<int> succ = s.get_succ(color);

	if(succ.size() <= 0)
		return scout(s, depth - 1, !color);
	else
	{

		state_t new_s = s.move(color, succ[0]);
		//int v = scout(new_s, depth - 1, !color);

		int v;
		hash_table_t::const_iterator it = tabla.find(new_s);
			if(it == tabla.end())
			{
				v = scout(new_s, depth - 1, !color);
				tabla.insert(std::make_pair(new_s, v));
			}
			else
				v = it->second;

		
		for(int i = 1; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);
			
			if(color && test(new_s, depth - 1, v, !color, MAYOR))
				v = scout(new_s, depth - 1, !color);

			if(!color && test(new_s, depth - 1, v, !color, MENOR))
				v = scout(new_s, depth - 1, !color);
		}

		return v;
	}
	return 0;
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

	if(succ.size() <= 0)
		return -negaScout(s, depth - 1, -betha, -alpha, !color);
	else
	{
		for(int i = 0; i < succ.size(); ++i)
		{
			state_t new_s = s.move(color, succ[i]);

			value = -negaScout(new_s, depth - 1, -bestValueN, -MAX(alpha, bestValueM), !color);

			if(value > bestValueM)
			{
				if((bestValueN == betha) || (depth < 3) || (value >= betha))
					bestValueM = value;
				else
					bestValueM = -negaScout(new_s, depth - 1, -betha, -value, !color);
			}

			if(bestValueM >= betha)
				return bestValueM;

			bestValueN = MAX(alpha, bestValueM) + 1;
		}
	}

	return bestValueM;
}

