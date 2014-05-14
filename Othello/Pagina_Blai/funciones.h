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

const int _INF = INT_MIN;
const int INF = INT_MAX;

/*Declaracion de funciones utilizadas en Funciones.c*/
extern int miniMax(state_t s, int depth, bool max);
