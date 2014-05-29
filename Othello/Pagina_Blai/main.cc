/**
 * Proyecto 2: Othello
 *
 * Inteligencia Artificial (CI5437)
 *
 * Copyright (C) 2012 Universidad Simon Bolivar
 * Author: Blai Bonet, bonet@ldc.usb.ve
 * Last revision: 11/08/2012
 *
 * Modified by:
 * 	 Stefano De Colli	09-10203
 *   Oskar González		09-10351
 *   Karen Troiano		09-10855
 *
 */

#include "funciones.h"

using namespace std;

int main(int argc, const char **argv)
{
	state_t state;
	int depth = 0;
	bool player = true;
	int result = 0;
	int opcion;
	int seed = 0;

	cout << "Seleccione la profundidad:" << endl;
	cout << endl;
	cin >> depth;

	while(depth <= 0)
	{
		cout << "Valor incorrecto de profundidad" << endl;
		cout << "Intente nuevamente:" << endl;
		cin >> depth;
	}

	for(int i = 0; i < depth; ++i)
	{
		player = i % 2 == 0; // black moves first
		int pos = PV[i];
		state = state.move(player, pos);
	}

	player = !player;
	seed = player ? 1 : -1;

	cout << "Seleccione el algoritmo a ejecutar:" << endl;
	cout << "0. Minimax" << endl;
	cout << "1. Minimax con alpha beta prunning" << endl;
	cout << "2. Negamax" << endl;
	cout << "3. Negamax con alpha beta prunning" << endl;
	cout << "4. Scout" << endl;
	cout << "5. Negascout" << endl;
	cout << endl;
	cin >> opcion;

	if(opcion >= 0 && opcion <= 5)
	{
		switch(opcion)
		{
		case(0):
			result = miniMax(state, depth, player);
			cout << "Resultado de Minimax: " << result << endl;
			break;
		case(1):
			cout << "d=" << 33 - depth << endl;
			result =  miniMaxAB(state, 33 - depth, _INF, INF, player);
			cout << "Resultado de Minimax con alpha beta prunning: " << result << endl;// << state << endl << state.hash() << endl;
			break;
		case(2):
			result = seed * negamax(state,depth, player);
			cout << "Resultado de Negamax: " << result << endl;
			break;
		case(3):
			result = seed * negamaxAB(state, depth, _INF, INF, player);
			cout << "Resultado de Negamax con alpha beta prunning: " << result << endl;
			break;
		case(4):
			result = seed * scout(state, depth, player);
			cout << "Resultado de Scout: " << result << endl;
			break;
		case(5):
			result = seed * negaScout(state, 33 - depth, _INF, INF, player);
			cout << "Resultado de Negascout: " << result << endl;
			break;
		}
	}
	else
		cout << "Opcion no valida" << endl;


	return 0;
}
