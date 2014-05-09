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
 * Ultima modificacion: 29/10/2012
 */

#include "othello_cut.h"
#include <iostream>
#include <limits.h>

using namespace std;

const int NEG_INF = INT_MIN;	//-infinite
const int INF = INT_MAX;		// infinite

/**
 * Algoritmo MinMax con los dos procedimientos mutuamente recursivos
 * valor_max() y valor_min()
 */

/** 
 * Declaracion del procemiento valor_min() la implementacion esta un poco
 * mas abajo. Asi logramos la recursion mutua
 */
int valor_min(state_t n, int d);

/**
 * valor_max() es el procedimiento que represanta al jugador Max
 * \param state_t n el estado actual del tablero de Othello
 * \param int d la profundidad del arbol de juego
 * \return el valor maximo del nodo Max
 */
int valor_max(state_t n, int d){ 
	vector<int> suc = n.get_moves(true);
	
	if(d == 0 || n.terminal())
		return n.value();
	if(suc.empty() && !n.terminal()) {

		int valormax = valor_min(n,d-1);

		return valormax;
	}else{
		int valormax = NEG_INF;
		for(int i = 0; i < suc.size(); ++i) {

			state_t next_n = n.move(true, suc[i]);
			valormax = max(valormax, valor_min(next_n,d-1));
		}
	
		return valormax;
	}
	 
}
/**
 * valor_min() es el procedimiento que represanta al jugador MIN
 * \param state_t n el estado actual del tablero de Othello
 * \param int d la profundidad del arbol de juego
 * \return el valor minimo del nodo Min
 */
int valor_min(state_t n, int d){ 
	vector<int> suc = n.get_moves(false);
	
	if(d == 0 || n.terminal())
		return n.value();
	if(suc.empty() && !n.terminal()) {

		int valormin = valor_max(n,d-1);

		return valormin;
	}else{
		int valormin = INF;
		for(int i = 0; i < suc.size(); ++i) {

			state_t next_n = n.move(false, suc[i]);

			valormin = min(valormin, valor_max(next_n,d-1));
		}
	
		return valormin;
	}
	 
}

/**
 * minmax() es el procedimiento para iniciar el algoritmo Minmax para arboles
 * de juego
 * \param state_t n el estado actual del tablero de Othello
 * \param int d la profundidad del arbol de juego
 * \return el valor maximo del nodo raìz Max
 */
int minmax(state_t n, int d){ 
	int respuesta = valor_max(n,d);
	return respuesta;
}
/**
 * alpha_betha_pruning
 * \param 
 * \return 
 */
int alpha_betha_pruning(state_t n, int d, int a, int b, bool t) {
	vector<int> suc = n.get_moves(t);
	if(n.terminal() || d == 0) {
		//cout << "Heuristica "<< n.value() << endl;
		return n.value();
	}
	if(suc.empty() && !n.terminal()) {
		cout << "Pasa "<< t << endl;
		
		
		if(t) {	// MAX
			int new_a = alpha_betha_pruning(n, d-1, a, b, false);
			a = max(a, new_a);
			//cout << "alpha "<< a << " betha " << b << endl;
		return a;
	} else {	// MIN
			int new_b = alpha_betha_pruning(n, d-1, a, b, true);
			b = min(b, new_b);
			//cout << "alpha "<< a << " betha " << b << endl;
		return b;
	}

	} else {
	if(t) {	// MAX
		for(int i = 0; i < suc.size(); ++i) {
			//cout << "Jugada de MAX "<< suc[i] << endl;
			state_t next_n = n.move(t, suc[i]);
			//cout << next_n;
			//char c;
			//cin >> c;
			int new_a = alpha_betha_pruning(next_n, d-1, a, b, false);
			a = max(a, new_a);
			//cout << "alpha "<< a << " betha " << b << endl;
			if(a >= b)
				break;
		}
		return a;
	} else {	// MIN
		for(int i = 0; i < suc.size(); ++i) {
			//cout << "Jugada de MIN "<< suc[i] << endl;
			state_t next_n = n.move(t, suc[i]);
			//cout << next_n;
			//char c;
			//cin >> c;
			int new_b = alpha_betha_pruning(next_n, d-1, a, b, true);
			b = min(b, new_b);
			//cout << "alpha "<< a << " betha " << b << endl;
			if(a >= b)
				break;
		}
		return b;
	}}
}

/**
 * Programa principal
 * \param argc numero de argumentos ingresados
 * \param argv lista de argumentos ingresados
 * \return 0 en caso de exito, -1 en caso de error
 */
int main(int argc, const char **argv) {
    state_t state;	// Initial state
    int d = 33;	// PV's deep
    bool player = true;		// Black moves first. They're MAX
    int result = 0;
    
	
	
	cout << state;
    for( int i = 0; i < 14; ++i ) {
        player = i % 2 == 0; // black moves first!
        int pos = PV[i];	// AQUI DEBEMOS SACAR LAS POSICIONES DE LOS SUCESORES
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);
       cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
		cout << state;
    }
	
	
	
    // Minimax
    result = minmax(state, d);
	cout << "Result of minmax: " << result << endl;
    
    // alpha_betha_pruning
    //result = alpha_betha_pruning(state, d, NEG_INF, INF, player);
	//cout << "Result of alpha_betha_pruning: " << result << endl;
    
    // Negascout
    
    
    
    /*cout << "Principal variation:" << endl;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];	// AQUI DEBEMOS SACAR LAS POSICIONES DE LOS SUCESORES
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

    if( argc > 1 ) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for(int i = 0; i < n; ++i ) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << state;
		
		vector<int> valid_moves = state.get_moves(1);
        for (int i = 0; i < valid_moves.size(); ++i) {
			cout << valid_moves[i] << endl;
		}
		
		cout << "Heuristica aqui es: " << state.h(1) << endl;
		
    }*/

    return 0;
}
