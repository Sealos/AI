#include "othello_cut.h"

using namespace std;
int out = -1;

int alpha_beta_prunning(state_t n, int alpha, int beta, bool color){
  if (n.terminal()){
    return n.value() * (color ? 1 : -1);
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


int minMax(state_t n,bool color) {
  int alpha;
  if (n.terminal() ){
    return n.value() * (color ? 1 : -1);
  }


  alpha = -2147483647;
  bool succ= false;

  for( int pos = 0; pos < DIM or (pos == DIM and !succ); ++pos ) {

    if( (color && n.is_black_move(pos)) || (!color && n.is_white_move(pos)) ) {

      succ=true;
      int aux = alpha;
      int m_M=-minMax(n.move(color,pos),!color);
      alpha= MAX(alpha,m_M);

      if (alpha!=aux){
        out=pos;
      }
    }

 }

 return alpha;

}

int main(int argc, char* argv[]){

    bool color = true;
    state_t root = state_t();
    int tr=atoi(argv[1]);
    int al=atoi(argv[2]);
    int v;
    state_t val[32];
    if (tr!=-1){
    for (int i = 0 ; i <= tr; i++){
        root =root.move(color,PV[i]);
        color=!color;
        cout << root;
        }
        
        switch (al) {
        case(0): v = alpha_beta_prunning(root, -2147483647, 2147483647,color); break;
        case(1): v = minMax(root,color); break;
        case(2): /*int v = negascout();*/ break;
        }
        }else{
       // cout << "hola" << endl;
        for (int i = 0 ; i <= 32; i++){
        val[i]=root;
        root =root.move(color,PV[i]);
        color=!color;
        //cout << root;
        }
        
       // cout << "hola1" << endl;
        switch (al) {
      
        case(0):

        for(int i=32; i>=0 ; i--){
         cout << "altura: " << 32-i << endl; 
	 //cout << "color: " << !color << endl;
         v = alpha_beta_prunning(val[i], -2147483647, 2147483647,!color);
         color=!color; 
         cout << v << endl;
         
         }
         break;

        case(1): 
	  for(int i=32; i>=0 ; i--){
         cout << "altura: " << 32-i << endl; 
	 cout << "color: " << !color << endl;
         v =minMax(val[i],!color);
         color=!color; 
         cout << v << endl;
	 /*v = minMax(root,!color);*/
	  }
	 break;
        case(2): /*int v = negascout();*/ break;
        
        }
        }
        /*for (int indice_local = 0; indice_local < indice_caso; ++indice_local){
            root = root.move(color,PV[indice_local]);
            color = (color + 1) % 2;
        }
        int v = alpha_beta_prunning(root, -2147483647, 2147483647,color);
        state_t result = state_t(v);*/
       
        return 0;
    }
    /*
    
  /*state_t root = state_t();
  root=root.move(true,12);
  cout << root;
  root=root.move(!true,21);
  cout << root;
  root=root.move(true,26);
  cout << root;
  root=root.move(!true,13);
  cout << root;
  root=root.move(true,22);
  cout << root;
  root=root.move(!true,18);
  cout << root;
  root=root.move(true,7);
  cout << root;
  root=root.move(!true,6);
  cout << root;
  root=root.move(true,5);
  cout << root;
  root=root.move(!true,27);
  cout << root;
  root=root.move(true,33);
  cout << root;
  root=root.move(!true,23);
  cout << root;
  root=root.move(true,17);
  cout << root;
  root=root.move(!true,11);
  cout << root;
  root=root.move(true,19);
  cout << root;
  //root=root.move(!true,15);
  cout << root;
  //root=root.move(true,14);
  cout << root;i
  //root=root.move(!true,31);
  cout << root;
  //root=root.move(true,20);
  cout << root;
  //root=root.move(!true,32);
  cout << root;
  //root=root.move(true,30);
  cout << root;
  // root=root.move(!true,10);
  cout << root;
  //root=root.move(true,25);
  cout << root;
  //  root=root.move(!true,24);
  cout << root;
  //root=root.move(true,34);
  cout << root;
  //root=root.move(!true,28);
  cout << root;
  // root=root.move(true,16);
  cout << root;
  // root=root.move(!true,4);
  cout << root;
  // root=root.move(true,29);
  cout << root;
  // root=root.move(!true,35);
  cout << root;
  //  root=root.move(true,36);
  cout << root;
  //root=root.move(!true,8);
  cout << root;
  //root=root.move(true,9);
  cout << root;
  cout << "Valor:";
  cout << root.value() << endl;

  vector<int> pepe;
  int v = alpha_beta_prunning(root, -2147483647, 2147483647,!true);
  state_t result = state_t(v);
  cout << v << endl;
  cout << out << endl;*/

  
  
