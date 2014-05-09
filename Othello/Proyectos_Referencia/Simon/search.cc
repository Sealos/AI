#include "othello_cut.h"
#include <iostream>
#include <climits>
#include <utility>
#include <algorithm>
#include <tr1/unordered_map>

#define PROF 100
#define ES_VALOR 0
#define ES_SUPERIOR 1
#define ES_INFERIOR -1
#define NO_ESTA (-2)

using namespace std;

#ifdef USE_HASH_TABLE
struct stored_info_t {
  int vBlack, vWhite;
  bool isBlack, isWhite;
  int sigBlack, sigWhite;
  int depth;
  stored_info_t() {
    isBlack = false;
    isWhite = false;
  }
  stored_info_t(int value_, bool is_max, int depth_) {
    if (is_max) {
      vBlack = value_;
      isBlack = true;
      isWhite = false;
    } else {
      vWhite = value_;
      isWhite = true;
      isBlack = false;
    }
    depth = depth_;
  }
    
  stored_info_t(int value_, int sig, bool is_max) {
    if (is_max) {
      vBlack = value_;
      isBlack = true;
      isWhite = false;
      sigBlack = sig;
    } else {
      vWhite = value_;
      isWhite = true;
      isBlack = false;
      sigWhite = sig;
    }
  }
};

struct hash_function_t : public tr1::hash<state_t> {
  size_t operator()(const state_t &state) const {
    return state.hash();
  }
};

// typedef hash_table_t tr1::unordered_map<state_t, stored_info_t, hash_function_t>
class hash_table_t : public tr1::unordered_map<state_t, stored_info_t, hash_function_t> {
};

hash_table_t my_hash_table;

//----------------REVISAR-EN-HASH----------------

pair<int,int> esta_en_hash (const state_t& state, bool is_max) {
    
  // Descomentar para inhabilitar tabla de hash
  //return make_pair(false,0);
	
  hash_table_t::iterator it;
  it = my_hash_table.find(state);
  if (it != my_hash_table.end() && is_max && it->second.isBlack){
    return make_pair(it->second.sigBlack,it->second.vBlack);
  }else if (it != my_hash_table.end() && !is_max && it->second.isWhite) {
    return make_pair(it->second.sigWhite,it->second.vWhite);
  }
  return make_pair(NO_ESTA,0);
}
void actualizar_hash (const state_t& state, int value, bool is_max) {
    
  // Descomentar para inhabilitar tabla de hash
  //return;

  hash_table_t::iterator it;
  it = my_hash_table.find(state);
  if (it != my_hash_table.end() && is_max) {
    it->second.vBlack = value;
    it->second.isBlack = true;
  } else if (it != my_hash_table.end() && !is_max) {\
    it->second.vWhite = value;
    it->second.isWhite = true;
  } else  {
    stored_info_t info(value,is_max);
    my_hash_table.insert(make_pair(state, info));
  }
}

void actualizar_hash_con_significado (const state_t& state, int value, int sig, bool is_max, int depth) {
    
  // Descomentar para inhabilitar tabla de hash
  // return;
    
  hash_table_t::iterator it;
  it = my_hash_table.find(state);
  if (it != my_hash_table.end() && is_max) {
    it->second.vBlack = value;
    it->second.sigBlack = sig;
    it->second.isBlack = true;
    it->depth = depth;
  } else if (it != my_hash_table.end() && !is_max) {
    it->second.vWhite = value;
    it->second.sigWhite = sig;
    it->second.isWhite = true;
    it->depth;
  } else {
    stored_info_t info(value,sig,is_max, depth);
    my_hash_table.insert(make_pair(state, info));
  } 
}
#endif


//----------------MINIMAX-------------------

int minimax_F (state_t state, int distance);
int minimax_G (state_t state, int distance);

int MINIMAX (state_t state, bool is_max) {
#ifdef USE_HASH_TABLE
  my_hash_table.clear();
#endif
    
  if (is_max)
    return minimax_F(state,PROF);
  else
    return minimax_G(state,PROF);
}


int minimax_F (state_t state, int distance) {

  if (state.terminal() || (distance == 0))
    return state.value();
#ifdef USE_HASH_TABLE	
  pair<int,int> esta = esta_en_hash(state,true);
  if (esta.first != NO_ESTA)
    return esta.second;
#endif 
  std::vector<state_t> succ = state.get_valid_states(true);
  int alpha = INT_MIN;
  for (int i=0; i < succ.size(); i++) {
    alpha = max(alpha, minimax_G(succ[i], distance-1));
  }

#ifdef USE_HASH_TABLE	
  actualizar_hash(state,alpha,true);
#endif
  return alpha;
}

int minimax_G (state_t state, int distance) {
	
  if (state.terminal() || (distance == 0))
    return state.value();
	
#ifdef USE_HASH_TABLE
  pair<int,int> esta = esta_en_hash(state,false);
  if (esta.first != NO_ESTA)
    return esta.second;
#endif

  std::vector<state_t> succ = state.get_valid_states(false);
  int alpha = INT_MAX;
  for (int i=0; i < succ.size(); i++) {
    alpha = min(alpha, minimax_F(succ[i], distance-1));
  }

#ifdef USE_HASH_TABLE	
  actualizar_hash(state,alpha,false);
#endif
  return alpha;
}

//----------------ALPHA-BETA-PRUNING-------------------

int alpha_beta_pruning (state_t state, int distance, int alpha, int beta, bool is_max) {

  if (state.terminal() || distance == 0)
    return state.value();

  if (is_max) {
#ifdef USE_HASH_TABLE
    pair<int,int> esta = esta_en_hash(state,true);
    if (esta.first == ES_VALOR) {
      return esta.second;
    } else if (esta.first == ES_INFERIOR) {
      alpha = max(alpha, esta.second);
    } else if (esta.first == ES_SUPERIOR) {
      beta = min(beta, esta.second);
    }
#endif
		
    std::vector<state_t> succ = state.get_valid_states(true);
    int m = alpha;
    for (int i=0; i < succ.size(); i++) {
      m = max(m, alpha_beta_pruning(succ[i], distance-1, m, beta, false));
      if (m >= beta)
	break;
    }
#ifdef USE_HASH_TABLE
    if (m <= alpha) {
      actualizar_hash_con_significado(state,m,ES_INFERIOR,true, distance);
    } else if (m >= beta) {
      actualizar_hash_con_significado(state,m,ES_SUPERIOR,true, distance);
    } else {
      actualizar_hash_con_significado(state,m,ES_VALOR,true, distance);
    }
#endif		
    return m;
  } else {
#ifdef USE_HASH_TABLE
    pair<bool,int> esta = esta_en_hash(state,false);
    if (esta.first == ES_VALOR) {
      return esta.second;
    } else if (esta.first == ES_INFERIOR) {
      alpha = esta.second;
    } else if (esta.first == ES_SUPERIOR) {
      beta = esta.second;
    }
#endif
		
    std::vector<state_t> succ = state.get_valid_states(false);
    int m = beta;
    for (int i=0; i < succ.size(); i++) {
      m = min(m, alpha_beta_pruning(succ[i], distance-1, alpha, m, true));
      if (alpha >= m)
	break;
    }
#ifdef USE_HASH_TABLE
    if (m <= alpha) {
      actualizar_hash_con_significado(state,m,ES_INFERIOR,false, distance);
    } else if (m >= beta) {
      actualizar_hash_con_significado(state,m,ES_SUPERIOR,false, distance);
    } else {
      actualizar_hash_con_significado(state,m,ES_VALOR,false, distance);
    }
#endif		
    return m;
  }
}

int ABP(state_t state, bool is_max) {
#ifdef USE_HASH_TABLE
  my_hash_table.clear();
#endif
  return alpha_beta_pruning (state,PROF,INT_MIN,INT_MAX,is_max);
}

//----------------SCOUT-ALPHA-BETA-PRUNING-------------------

int SABP_G (state_t state, int distance, int alpha, int beta);
int SABP_F (state_t state, int distance, int alpha, int beta);

int SABP (state_t state, bool is_max) {
#ifdef USE_HASH_TABLE
  my_hash_table.clear();
#endif
  if (is_max)
    return SABP_F(state,PROF,INT_MIN,INT_MAX);
  else
    return SABP_G(state,PROF,INT_MIN,INT_MAX);
}

int SABP_F (state_t state, int distance, int alpha, int beta) {

  if (state.terminal() || distance == 0)
    return state.value();

#ifdef USE_HASH_TABLE
  pair<int,int> esta = esta_en_hash(state,true);
  if (esta.first == ES_VALOR) {
    return esta.second;
  } else if (esta.first == ES_INFERIOR) {
    alpha = max(alpha, esta.second);
  } else if (esta.first == ES_SUPERIOR) {
    beta = min(beta, esta.second);
  }
#endif
	
  int m = INT_MIN;
  std::vector<state_t> succ = state.get_valid_states(true);
  m = max(m, SABP_G(succ[0], distance-1, alpha, beta));
  if (m >= beta) {
#ifdef USE_HASH_TABLE
    actualizar_hash_con_significado(state,m,ES_SUPERIOR,true, distance);
#endif
    return m;
  }
  int t;
  for (int i=1; i < succ.size(); i++) {
    t = SABP_G(succ[i], distance-1, m, m+1);
    if (t > m) {
      if (t>= beta)
	m = t;
      else
	m = SABP_G(succ[i], distance-1, t, beta);
    }
    if (m >= beta) {
#ifdef USE_HASH_TABLE
      actualizar_hash_con_significado(state,m,ES_SUPERIOR,true, distance);
#endif
      return m;
    }
  }

#ifdef USE_HASH_TABLE	
  if (m > alpha)
    actualizar_hash_con_significado(state,m,ES_VALOR,true, distance);
  else
    actualizar_hash_con_significado(state,m,ES_INFERIOR,true, distance);
#endif
  return m;
}

int SABP_G (state_t state, int distance, int alpha, int beta) {

  if (state.terminal() || distance == 0)
    return state.value();
#ifdef USE_HASH_TABLE
  pair<int,int> esta = esta_en_hash(state,false);
  if (esta.first == ES_VALOR) {
    return esta.second;
  } else if (esta.first == ES_INFERIOR) {
    alpha = max(alpha, esta.second);
  } else if (esta.first == ES_SUPERIOR) {
    beta = min(beta, esta.second);
  }
#endif

	
  int m = INT_MAX;
  std::vector<state_t> succ = state.get_valid_states(false);
  m = min(m, SABP_F(succ[0], distance-1, alpha, beta));
  if (m <= alpha) {
#ifdef USE_HASH_TABLE
    actualizar_hash_con_significado(state,m,ES_INFERIOR,false, distance);
#endif
    return m;
  }
  int t;
  for (int i=1; i < succ.size(); i++) {
    t = SABP_F(succ[i], distance-1, m, m+1);
    if (t <= m) {
      if (t<= alpha)
	m = t;
      else
	m = SABP_F(succ[i], distance-1, alpha, t);
    }
    if (m <= alpha) {
#ifdef USE_HASH_TABLE
      actualizar_hash_con_significado(state,m,ES_INFERIOR,false, distance);
#endif
      return m;
    }
  }

#ifdef USE_HASH_TABLE	
  if (m < beta)
    actualizar_hash_con_significado(state,m,ES_VALOR,false, distance);
  else
    actualizar_hash_con_significado(state,m,ES_SUPERIOR,false, distance);
#endif
  return m;
}
