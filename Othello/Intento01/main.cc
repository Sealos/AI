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

// ALPHA-BETA PRUNING

int alpha_beta_pruning(state_t n, int d, int a, int b, bool t) {
	if(n.terminal() || d == 0)
		return n.value();
	vector<int> suc = n.get_moves(t);
	if(suc.empty() && !n.terminal()) {	// the player pass
		if(t)	// MAX
			return std::max(a, alpha_beta_pruning(n, d - 1, a, b, false));
		else	// MIN
			return std::min(b, alpha_beta_pruning(n, d - 1, a, b, true));
	} else {
		if(t) {		// MAX
			for(int i = 0; i < suc.size(); ++i) {
				state_t new_n = n.move(t, suc[i]);
				a = std::max(a, alpha_beta_pruning(new_n, d - 1, a, b, false));
				if(a >= b)
					break;
			}
			return a;
		} else {	// MIN
			for(int i = 0; i < suc.size(); ++i) {
				state_t new_n = n.move(t, suc[i]);
				b = std::min(b, alpha_beta_pruning(new_n, d - 1, a, b, true));
				if(a >= b)
					break;
			}
			return b;
		}
	}
}

int miniMaxAB(state_t &s, int depth, int alpha, int betha,  bool max)
{
	if(s.terminal() || depth == 0)
		return s.value();

	if(max)
	{
		std::vector<int> succ = s.get_succ(true);
		
		if(succ.empty()) {
			return miniMaxAB(s, depth - 1, alpha, betha, false);
		} 
		else {
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(true, succ[i]);
				int val = miniMaxAB(new_s, depth - 1, alpha, betha, false);
				
				alpha = std::max(alpha, val);
				
				if(alpha >= betha)
					break;
			}
			
			return alpha;
		}
		
	}
	else
	{
		std::vector<int> succ = s.get_succ(false);
		
		if(succ.empty()) {
			return miniMaxAB(s, depth - 1, alpha, betha, true);
		} 
		else {
			for(int i = 0; i < succ.size(); ++i)
			{
				state_t new_s = s.move(false, succ[i]);
				int val = miniMaxAB(new_s, depth - 1, alpha, betha, true);
				
				betha = std::min(betha, val);

				if(alpha >= betha)
					break;
			}
			
			return betha;
		}
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


	for(int i = 0; i < depth; ++i)
	{
		player = i % 2 == 0; // black moves first
		state = state.move(player, PV[i]);
	}

	player = !player;
	seed = player ? 1 : -1;
	
	cout << "d=" << 33 - depth << endl;
	result =  miniMaxAB(state, 33 - depth, _INF, INF, player);
	cout << "Resultado de Minimax con alpha beta prunning: " << result << endl;// << state << endl << state.hash() << endl;
	result = alpha_beta_pruning(state, 33 - depth, _INF, INF, player);
	cout << "Resultado de con alpha beta prunning: " << result << endl;// << state << endl << state.hash() << endl;
	
 /*   cout << "Principal variation:" << endl;
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

