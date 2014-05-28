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

#include "othello_cut.h"
#include <limits.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <climits>
#include <list>

const int _INF = -100;//INT_MIN;
const int INF = 100;//INT_MAX;

/*Declaracion de funciones utilizadas en Funciones.cpp*/
extern int miniMax(state_t s, int depth, bool max);
extern int miniMaxAB(state_t &s, int depth, int alpha, int betha,  bool max);
extern int negamax(state_t s, int depth, bool color);
extern int negamaxAB(state_t s, int depth, int alpha, int betha, bool color);
extern int negaScout(state_t s, int depth, int alpha, int betha, bool color);
