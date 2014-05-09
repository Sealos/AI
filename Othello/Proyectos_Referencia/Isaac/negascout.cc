#include "othello_cut.h"
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;


/*int negascout(state_t s, int alpha, int beta, bool color) {
  if (s.terminal())
     return s.value() * (color ? 1 : -1);
  int b = beta;
  bool color_ = color;
  vector<int> succ_ = s.succ(color_);
  int _succ = succ_.size();
  
  if(!_succ) {
    color_ = !color; 
    succ_ = s.succ(color_);
  }
  
  for(vector<int>::const_iterator iter=succ_.begin(),limit=succ_.end();iter!=limit;++iter) {
    state_t n = s.move(color_,*iter);
    int score = -negascout(n,-b,-alpha,!color_);
	if ((alpha < score) && (score < beta) && (*iter!=*(succ_.begin())))
	  score = -negascout(n,-beta,-alpha,!color_);
    alpha = max(alpha,score);
    if (alpha >= beta)
      return alpha;
    b = alpha + 1;	  
  }
  return alpha;
}*/

int G_(state_t s, int alpha, int beta, bool color);

int F_(state_t s, int alpha, int beta, bool color) {
  if (s.terminal())
    return s.value() * (color ? 1 : -1);
	
  int m = numeric_limits<signed int>::min();
  
  bool color_ = color;
  vector<int> succ_ = s.succ(color_);
  int _succ = succ_.size();
  
  state_t n;
  
  if (_succ) { 
    n = s.move(color_,succ_.front());
	
    m = max(m,G_(n,alpha,beta,!color_));
    if(m >= beta)
      return m;
  
    for(vector<int>::const_iterator iter=succ_.begin(),limit=succ_.end();iter!=limit;++iter) {
      if (iter != succ_.begin()) {
	    n = s.move(color_,*iter);
	    int t = G_(n,m,m + 1,!color_);
	    if (t > m) {
          if (t >= beta) 
             m = t;
          else
             m = G_(n,t,beta,!color_);
		}
        if (m >= beta)
          return m;
	  }
    }
  }
  else {
    m = max(m,G_(s,alpha,beta,!color_));
	if(m >= beta)
      return m;
	  
	int t = G_(s,m,m + 1,!color_);
	if (t > m) {
      if (t >= beta) 
         m = t;
      else
         m = G_(s,t,beta,!color_);
	}
  }  
  
  return m;
}

int G_(state_t s, int alpha, int beta, bool color) {
  if (s.terminal())
    return s.value() * (color ? 1 : -1);
	
  int m = numeric_limits<signed int>::max();
   
  bool color_ = color;
  vector<int> succ_ = s.succ(color_);
  int _succ = succ_.size();
  
  state_t n;
  
  if (_succ) {
    n = s.move(color_,succ_.front());
    m = min(m,F_(n,alpha,beta,!color_));
    if(m <= alpha)
      return m;

    for(vector<int>::const_iterator iter=succ_.begin(),limit=succ_.end();iter!=limit;++iter) {
      if (iter!=succ_.begin()) {
	    n = s.move(color_,*iter);
	    int t = F_(n,m,m + 1,!color_);
	    if (t <= m){
          if (t <= alpha) 
            m = t;
          else
            m = F_(n,alpha,t,!color_);
		}
        if (m <= alpha)
          return m;	  
	  }
    }
  }
  else {
    m = min(m,F_(s,alpha,beta,!color_));
    if(m <= alpha)
      return m;
	  
	int t = F_(s,m,m + 1,!color_);
	if (t <= m){
      if (t <= alpha) 
         m = t;
      else
         m = F_(s,alpha,t,!color_);
	}
  }
  
  return m;
}

int negascout(state_t s, int alpha, int beta, bool color) {
  if (color)
    return F_(s,alpha,beta,color);
  else
    return G_(s,alpha,beta,color);
}

/*int Nega_Scout(state_t s, int alpha, int beta, bool color) {
  if (s.terminal())
    return s.value() * (color ? 1 : -1);

  bool color_ = color;
  vector<int> succ_ = s.succ(color_);
  int _succ = succ_.size();
 
  
  // Pasar el turno al jugador contrario
  if(!_succ) {
    color_ = !color; 
    succ_ = s.succ(color_);
  }
  
  int a = alpha, b = beta;
  
  for(vector<int>::const_iterator iter=succ_.begin(),limit=succ_.end();iter!=limit;++iter) {
    state_t n = s.move(color_,*iter);
    int t = -Nega_Scout(n,-b,-a,!color_);
	if((t > a) && (t < beta) && ((*iter) != succ_.front()))
	  a = Nega_Scout(n,-beta,-t,!color_);
	a = max(a,t);
	if(a >= beta)
	  return a;
	b = a + 1;
  }
  return a;
}*/

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
 root=root.move(true,14);
 cout << root << endl;
 root=root.move(!true,31);
 cout << root << endl;
 root=root.move(true,20);
 cout << root << endl;
 root=root.move(!true,32);
 cout << root << endl;
 root=root.move(true,30);
 cout << root << endl;
 /*root=root.move(!true,10);
 cout << root << endl;
 root=root.move(true,25);
 cout << root << endl;
 root=root.move(!true,24);
 cout << root << endl;
 root=root.move(true,34);
 cout << root << endl;
 root=root.move(!true,28);
 cout << root << endl;
 root=root.move(true,16);
 cout << root << endl;
 root=root.move(!true,4);
 cout << root << endl;
 root=root.move(true,29);
 cout << root << endl;
 root=root.move(!true,35);
 cout << root << endl;
 root=root.move(true,36);
 cout << root << endl;
 root=root.move(!true,8);
 cout << root << endl;
 root=root.move(true,9);
 cout << root << endl;*/
 cout << "Valor: " << root.value() << endl;
  
 int v = negascout(root,numeric_limits<signed int>::min(),numeric_limits<signed int>::max(),!true);
 
//std::vector<int> v();  
 cout << v << endl;
}
*/
