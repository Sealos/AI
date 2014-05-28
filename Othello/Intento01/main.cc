/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 11/08/2012
 *
 */

#include "othello_cut.h" // won't work correctly until .h is fixed!
#include <iostream>
#include <limits.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <climits>
#include <list>

const int _INF = INT_MIN;
const int INF = INT_MAX;

using namespace std;

/*
int alpha_beta_prunning(state_t n, int alpha, int beta, bool color){
  if (n.terminal()){
    return n.value();
  }

  vector<int> successors = n.get_succ(color);  
  if (successors.size()>0){
  if (color){
    for (vector<int>::iterator sucesores =successors.begin(), limit=successors.end(); sucesores != limit;++sucesores){
      int hijo = alpha_beta_prunning(n.move(color, *sucesores), alpha, beta, !color);
      alpha = MAX(alpha, hijo);
        if (alpha >= beta) { break; }
    }

    return alpha;

  } else {

    for (vector<int>::iterator sucesores =successors.begin(), limit=successors.end(); sucesores != limit; ++sucesores){
        int hijo = alpha_beta_prunning(n.move(color, *sucesores), alpha, beta, !color);
        beta = MIN(beta, hijo);
        if (alpha >= beta) { break; }
    }

    return beta;
  }
  }else{
    return alpha_beta_prunning(n,alpha,beta, !color);
  }
}*/

// ALPHA-BETA PRUNING

int miniMaxAB(state_t &s,  int alpha, int betha,  bool jugador)
{
	if(s.terminal())
		return s.value();

	std::vector<int> succ = s.get_succ(jugador);
	
	if (succ.size() > 0) {
	
		if(jugador) //MAX
		{
			for (vector<int>::iterator suc=succ.begin(), limit=succ.end(); suc != limit;++suc)
			{
				state_t new_s = s.move(jugador, *suc);
				alpha = MAX(alpha, miniMaxAB(new_s, alpha, betha, !jugador));
				
				if(alpha >= betha)
					break;
			}
			
			return alpha;
			
		}
		else
		{ //MIN
			for (vector<int>::iterator suc =succ.begin(), limit=succ.end(); suc != limit;++suc)
			{
				state_t new_s = s.move(jugador, *suc);
				
				betha = MIN(betha, miniMaxAB(new_s, alpha, betha, !jugador));

				if(alpha >= betha)
					break;
			}
			
			return betha;
		} 
	} else {
		return miniMaxAB(s, alpha, betha, !jugador);
	}

	return 0;
}

int main(int argc, const char **argv) {
   state_t state;
   
	int depth = 0;
	bool player = true;
	int result = 0;
	int opcion;
	int seed = 0;
   
	cout << "Seleccione la profundidad:" << endl;
	cout << endl;
	cin >> depth;

	while(depth <= 0 && depth >= 33)
	{
		cout << "Valor incorrecto de profundidad" << endl;
		cout << "Intente nuevamente:" << endl;
		cin >> depth;
	}

	for(int i = 0; i < depth; ++i) {
		bool player = i % 2 == 0; // black moves first!
		int pos = PV[i];
		state = state.move(player, pos);
	}

	player = (depth % 2 == 0);
	seed = player ? 1 : -1;
	
	cout << "d=" << state;
	cout << "d=" << 33 - depth << endl;
	result =  miniMaxAB(state, _INF, INF, player);
	cout << "Resultado de Minimax con alpha beta prunning: " << result << endl;// << state << endl << state.hash() << endl;
	/*result =  alpha_beta_prunning(state, _INF, INF, player);
	cout << "Resultado de Minimax con alpha beta prunning: " << result << endl;
 *//*   cout << "Principal variation:" << endl;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << state;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
    }
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;
*/
    return 0;
}

