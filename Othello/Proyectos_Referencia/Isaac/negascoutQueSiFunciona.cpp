#include "othello_cut.h"
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

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
    cout << "soy F" << endl;
  if (n.terminal()) {
    cout << " soy terminal y valgo: " << n.value() << endl;
    return n.value() ;//* (color ? 1 : -1);
  }
  
  int m = numeric_limits<signed int>::min();
  vector<int> succ_ = n.succ(color);
  if (succ_.size() != 0){
    cout << " voy a jugar: " << succ_.front() << endl;
    state_t jugada = n.move(color, succ_.front());
    cout << " hice jugada " << endl;
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
    cout << "soy G" << endl;
  if (n.terminal()) {
    cout << " soy terminal y valgo: " << n.value() << endl;
    return n.value() ;//* (color ? 1 : -1);;
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
        cout << " expando: " << *iter << endl;
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

int main() {
 state_t root = state_t();
 root=root.move(true,12);
 cout << root << endl;
 root=root.move(!true,21);
 cout << root << endl;;
 root=root.move(true,26);
 cout << root << endl;;
 root=root.move(!true,13);
 cout << root << endl;
 root=root.move(true,22);
 cout << root << endl;
 root=root.move(!true,18);
 cout << root << endl;
 root=root.move(true,7);
 cout << root << endl;
 root=root.move(!true,6);
 cout << root << endl;
 root=root.move(true,5);
 cout << root << endl;
 root=root.move(!true,27);
 cout << root << endl;
 root=root.move(true,33);
 cout << root << endl;
 root=root.move(!true,23);
 cout << root << endl;
 root=root.move(true,17);
 cout << root << endl;
 root=root.move(!true,11);
 cout << root << endl;
 root=root.move(true,19);
 cout << root << endl;
 root=root.move(!true,15);
 cout << root << endl;
 //root=root.move(true,14);
 cout << root << endl;
 //root=root.move(!true,31);
 cout << root << endl;
 //root=root.move(true,20);
 cout << root << endl;
 //root=root.move(!true,32);
 cout << root << endl;
 //root=root.move(true,30);
 cout << root << endl;
 //root=root.move(!true,10);
 cout << root << endl;
 //root=root.move(true,25);
 cout << root << endl;
 //root=root.move(!true,24);
 cout << root << endl;
 //root=root.move(true,34);
 cout << root << endl;
 //root=root.move(!true,28);
 //cout << root << endl;
 //root=root.move(true,16);
 //cout << root << endl;
 //root=root.move(!true,4);
 //cout << root << endl;
 //root=root.move(true,29);
 //cout << root << endl;
 //root=root.move(!true,35);
 //cout << root << endl;
 //root=root.move(true,36);
 //cout << root << endl;
 //root=root.move(!true,8);
 //cout << root << endl;
 //root=root.move(true,9);
 //cout << root << endl;
 cout << "Valor: " << root.value() << endl;
  
 int v = negascout(root,numeric_limits<signed int>::min(),numeric_limits<signed int>::max(),true);
 
//std::vector<int> v();  
 cout << v << endl;
}
