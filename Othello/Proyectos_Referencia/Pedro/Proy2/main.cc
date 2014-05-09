/**
 * Proyecto 2: Othello
 * 
 * Inteligencia Artificial (CI5437)
 * 
 * Game of Othello -- main
 * Universidad Simon Bolivar, 2012.
 * Author: Blai Bonet
 * Last Revision: 10/23/12
 * 
 * Modified by:
 * 	Andreina Garcia			08-10406
 * 	Jose Antonio Rodriguez	08-10971
 * 	Pedro Romero			08-10992
 * 
 * Ultima modificacion: 05/11/2012
 */

#include "othello_cut.h"
#include <iostream>
#include <limits.h>

using namespace std;

const int NEG_INF = INT_MIN;	// -infinite
const int INF = INT_MAX;		// infinite
int expanded;					// # expanded nodes
int created;					// # created nodes

// MINIMAX

// Declaration of the procesure valor_min
int valor_min(state_t n, int d);

/**
 * valor_max represents the player MAX
 * \param n actual state of board of Othello
 * \param d max dimension of search
 * \return maximum value of the game
 */
int valor_max(state_t n, int d){ 
	if(d == 0 || n.terminal())
		return n.value();
	vector<int> suc = n.get_moves(true);
	if(suc.empty() && !n.terminal()) {	// the player MAX pass
		return valor_min(n, d - 1);
	} else {
		++expanded;
		int valormax = NEG_INF;
		for(int i = 0; i < suc.size(); ++i) {
			state_t new_n = n.move(true, suc[i]);
			++created;
			valormax = max(valormax, valor_min(new_n, d - 1));
		}
		return valormax;
	}
	 
}

/**
 * valor_min represents the player MIN
 * \param n actual state of board of Othello
 * \param d max dimension of search
 * \return minimum value of the game
 */
int valor_min(state_t n, int d){ 
	if(d == 0 || n.terminal())
		return n.value();
	vector<int> suc = n.get_moves(false);
	if(suc.empty() && !n.terminal())	// the player MIN pass
		return valor_max(n, d - 1);
	else {
		++expanded;
		int valormin = INF;
		for(int i = 0; i < suc.size(); ++i) {
			state_t new_n = n.move(false, suc[i]);
			++created;
			valormin = min(valormin, valor_max(new_n, d - 1));
		}
		return valormin;
	}
	 
}

/**
 * minimax is the procedure that starts minimax for game trees.
 * It uses two mutually recursive procedures valor_max y valor_min.
 * \param n actual state of board of Othello
 * \param d max dimension of search
 * \return maximum value of the game
 */
int minimax(state_t n, int d) {
	return valor_max(n,d);
}

// ALPHA-BETA PRUNING

/**
 * alpha_beta_pruning is a search algorithm that seeks to decrease the number 
 * of nodes that are evaluated by the minimax algorithm in its search tree. 
 * \param n node of the search tree
 * \param d max dimension of search
 * \param a alpha value (inferior bound)
 * \param b beta value (superior bound)
 * \param t player
 * \return value of the best game found
 */
int alpha_beta_pruning(state_t n, int d, int a, int b, bool t) {
	if(n.terminal() || d == 0)
		return n.value();
	vector<int> suc = n.get_moves(t);
	if(suc.empty() && !n.terminal()) {	// the player pass
		if(t)	// MAX
			return max(a, alpha_beta_pruning(n, d - 1, a, b, false));
		else	// MIN
			return min(b, alpha_beta_pruning(n, d - 1, a, b, true));
	} else {
		++expanded;
		if(t) {		// MAX
			for(int i = 0; i < suc.size(); ++i) {
				state_t new_n = n.move(t, suc[i]);
				++created;
				a = max(a, alpha_beta_pruning(new_n, d - 1, a, b, false));
				if(a >= b)
					break;
			}
			return a;
		} else {	// MIN
			for(int i = 0; i < suc.size(); ++i) {
				state_t new_n = n.move(t, suc[i]);
				++created;
				b = min(b, alpha_beta_pruning(new_n, d - 1, a, b, true));
				if(a >= b)
					break;
			}
			return b;
		}
	}
}

// NEGASCOUT

// Declaration of the procesure G
int G(state_t n, int d, int alpha, int beta);

/**
 * F is a method of negascout algorithm. F search in a MAX node looking for 
 * a terminal state that is between alpha and beta. 
 * \param n node (MAX)
 * \param d max dimension of search
 * \param alpha inferior bound
 * \param beta superior bound
 * \return the value of the game
 */
int F(state_t n, int d, int alpha, int beta) {
    if(d == 0 || n.terminal()) 
		return n.value();
    vector<int> succ = n.get_moves(true);
    if(succ.empty() && !n.terminal())	// the player MAX pass
		return G(n, d - 1, alpha, beta);
	++expanded;
	int m = NEG_INF;
	state_t new_n = n.move(true, succ[0]);
	++created;
    int aux = G(new_n, d - 1, alpha, beta);
    if(aux > m) 
		m = aux;
    if(m >= beta) 
		return m;
    for(int i = 1; i < succ.size(); ++i) {
		new_n = n.move(true, succ[i]);
		++created;
        int t = G(new_n, d - 1, m, m + 1);
        if(t > m) {
            if(t >= beta)
                m = t;
            else
                m = G(new_n, d - 1, t, beta);
            if( m >= beta )
                return m;
        }
    }
    return m;
}

/**
 * G is a method of negascout algorithm. G search in a MIN node looking for 
 * a terminal state that is between alpha and beta. 
 * \param n node (MAX)
 * \param d max dimension of search
 * \param alpha inferior bound
 * \param beta superior bound
 * \return the value of the game 
 */
int G(state_t n, int d, int alpha, int beta){
    if(d == 0 || n.terminal()) 
		return n.value();
    vector<int> succ = n.get_moves(false);
    if(succ.empty() && !n.terminal()) 
		return F(n, d - 1, alpha, beta);
	++expanded;
	int m = INF;
	state_t new_n = n.move(false, succ[0]);
	++created;
    int aux = F(new_n, d - 1, alpha, beta);
    if(aux < m) 
		m = aux;
    if(m <= alpha) 
		return m;
    for(int i = 1; i < succ.size(); ++i) {
		new_n = n.move(false, succ[i]);
		++created;
        int t = F(new_n, d - 1, m, m + 1);
        if(t <= m){
            if(t <= alpha)
                m = t;
            else
                m = F(new_n, d - 1, alpha, t);
            if(m <= alpha)
                return m;
        }
    }
    return m;
}

/**
 * Principal
 * \param argc number of arguments
 * \param argv list of arguments (number of the algorithm and deep of PV)
 * \return 0 in case of success, -1 in case of failure
 */
int main(int argc, const char **argv) {
    state_t state;	// Initial state
    created = 1;
    bool player = true;		// Black moves first. They're MAX
    int result = 0;
	expanded = 0;
    int option = atoi(argv[1]);	/* 1. minimax
									 * 2. alpha-beta pruning
									 * 3. negascout */
	int deep = atoi(argv[2]);
	if(deep < 0 || deep % 2 != 0) {
		cout << "Incorrect argument deep" << endl;
		return -1;
	}
	int d = atoi(argv[3]);	// PV's deep
	if(d < 0) {
		cout << "Incorrect argument d" << endl;
		return -1;
	}
    for( int i = 0; i < deep; ++i ) {
        bool player = i % 2 == 0; // black moves first
        int pos = PV[i];
        state = state.move(player, pos);
    }
	switch(option) {
		case 1: // minimax
			result = minimax(state, d);
			cout << "Result of minimax: " << result << endl;
			break;
		case 2: // alpha_beta_pruning
			result = alpha_beta_pruning(state, d, NEG_INF, INF, player);
			cout << "Result of alpha_beta_pruning: " << result << endl;
			break;
		case 3: // negascout
			result = F(state,d,NEG_INF,INF);
			cout << "Result of negascout: " << result << endl;
			break;
		default:
			cout << "Incorrect argument option" << endl;
			return -1;
	}
	cout << "Expanded nodes: " << expanded << endl;
	cout << "Created nodes: " << created << endl;
    return 0;
}