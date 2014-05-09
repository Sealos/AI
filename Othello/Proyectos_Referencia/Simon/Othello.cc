// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 10/23/12
// Modified by: Alejandro Flores, Jonathan Queipo y Simón Castillo

#include <iostream>
#include <vector>
#include "search.cc"
#define USE_HASH_TABLE

using namespace std;

int main(int argc, const char **argv) {

  state_t state;
  vector<state_t> states;
  
  cout << "\nOthelo | Principal variation:\n" << endl;
  
  // Calculamos todos los estados de
  // la Variación Principal y las guardamos
  // en un vetor.
  for( int i = 0; PV[i] != -1; ++i ) {
    bool player = i % 2 == 0;
    int pos = PV[i];
  	states.push_back(state);
    state = state.move(player, pos);
  }
  cout << "Final state of the Principal Variation:" << endl;
  cout << state;
  cout << "Value of the game = " << state.value() << endl;
  
  char opt, algo;
  int n;
  while (true) {
    cout << "\nOptions:" << endl
         << "  (a) Search the game value of a state from the PV." << endl
         << "  (b) Search the game value of a state after N random moves." << endl
         << "  (c) Exit." << endl;
    cin >> opt;
    
    if (opt=='a') {
      
      cout << "Select the state index [0..32] from the PV: ";
      cin >> n;
      if (0>n || n>32) continue;
      
      cout << "Select the algorithm you want to use:" << endl
           << "  (a) MinMax." << endl
           << "  (b) Alpha-Beta Pruning." << endl
           << "  (c) Scout Alpha-Beta Pruning." << endl;
      cin >> algo;
      
      bool player = n % 2 == 0;
      int gameValue;
      
      if      (algo=='a') gameValue = MINIMAX(states[n],player);
      else if (algo=='b') gameValue = ABP(states[n],player);
      else                gameValue = SABP(states[n],player);
      
      cout << "State #" << n << " from the PV:" << endl;
      cout << states[n];
      cout << "Value of the game = " << gameValue << endl;
      
    } else if (opt=='b') {
      
      cout << "Choose the number of random moves you want to make: ";
      cin >> n;
      cout << "Select the algorithm you want to use:" << endl
           << "  (a) MinMax." << endl
           << "  (b) Alpha-Beta Pruning." << endl
           << "  (c) Scout Alpha-Beta Pruning." << endl;
      cin >> algo;
      
      state = state_t();
      int gameValue,i;
      bool player;
      for(i = 0; i < n; ++i ) {
        player = i % 2 == 0;
        int pos = state.get_random_move(player);
        state = state.move(player, pos);
        if (state.terminal())
          break;
      }
      
      if      (algo=='a') gameValue = MINIMAX(state,player);
      else if (algo=='b') gameValue = ABP(state,player);
      else                gameValue = SABP(state,player);
      
      cout << "State after " << i << " moves:" << endl;
      cout << state;
      cout << "Value of the game = " << gameValue << endl;
      
    } else {
      break;
    }
  }
  cout << endl;
  
  return 0;
}

