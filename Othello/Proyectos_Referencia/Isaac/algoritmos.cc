#include "othello_cut.h"
#include <limits>

using namespace std;

int out = -1;

int alpha_beta_prunning(state_t n, int alpha, int beta, bool color){
  if (n.terminal()){
    return n.value();
  }

  vector<int> successors = n.succ(color);  
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
}

int min_max(state_t n,bool color) {
  int alpha;
  if (n.terminal() ){
    return n.value() * (color ? 1 : -1);
  }

  alpha = numeric_limits<signed int>::min();
  bool succ = false;

  for( int pos = 0; pos < DIM or (pos == DIM and !succ); ++pos ) {

    if( (color && n.is_black_move(pos)) || (!color && n.is_white_move(pos)) ) {

      succ=true;
      int aux = alpha;
      int m_M=-min_max(n.move(color,pos),!color);
      alpha= MAX(alpha,m_M);

      if (alpha!=aux){
        out=pos;
      }
    }

 }
 return alpha;
}

int F_(state_t n, int alpha, int beta, bool color);
int G_(state_t n, int alpha, int beta, bool color);

int negascout(state_t n, int alpha, int beta, bool color){
	if (color) {
	  return F_(n, alpha, beta, color);
	} else {
	  return G_(n, alpha, beta, color);
  }
}

int F_(state_t n, int alpha, int beta, bool color) {
  if (n.terminal()) {
    return n.value() ;
  }
  
  int m = numeric_limits<signed int>::min();
  vector<int> succ_ = n.succ(color);
  
  if (succ_.size() != 0){
    state_t jugada = n.move(color, succ_.front());
    succ_.erase(succ_.begin());
    int valor = G_(jugada, alpha, beta, !color);
    m = MAX(m, valor);
    if ( m >= beta) {
      return m;
    }  
    
    for(vector<int>::const_iterator iter=succ_.begin(),limit=succ_.end();iter!=limit;++iter) {
        jugada = n.move(color, *iter);
        int t = G_(jugada,m,m + 1, !color);
        if(t > m) {
          if(t >= beta) {
            m = t;
          }
          else {
            m = G_(jugada, t, beta, !color);
          }
        }
        if(m >= beta) {
          return beta;
        }
    }
  } else {
    return G_(n.move(color, 36), alpha, beta, !color);
  }
  return m;
}

int G_(state_t n, int alpha, int beta, bool color) {
  if (n.terminal()) {
    return n.value();
  }
  
  int m = numeric_limits<signed int>::max();
  vector<int> succ_ = n.succ(color);
  if (succ_.size() != 0){
      state_t jugada = n.move(color, succ_.front());
      succ_.erase(succ_.begin());
      int valor = F_(jugada, alpha, beta, !color);
      m = MIN(m, valor);
      if ( m <= alpha) {
        return m;
      }  
      
      for(vector<int>::const_iterator iter=succ_.begin(),limit=succ_.end();iter!=limit;++iter) {
          jugada = n.move(color, *iter);
          int t = F_(jugada,m,m + 1,!color);
          if(t <= m) {
            if(t <= alpha) {
              m = t;
            }
            else {
              m = F_(jugada,alpha,t,!color);
            }
          }
          if(m <= alpha) {
            return alpha;
          }
      }
    } else {
        return F_(n.move(color, 36), alpha, beta, !color);
    }
  return m;
}