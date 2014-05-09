#include "algoritmos.cc"
#include <limits>

int main(int argc, char* argv[]){
  bool color = true;
  state_t root = state_t();
  int tr = atoi(argv[1]);
  int al = atoi(argv[2]);
  int v;
  state_t val[32];
  if (tr != -1){
    for (int i = 0 ; i <= tr; i++){
      root = root.move(color,PV[i]);
      color = !color;
      cout << root;
    }
    switch (al) {
      case(0): 
	    v = alpha_beta_prunning(root, numeric_limits<signed int>::min(), numeric_limits<signed int>::max(),color); 
		break;
      case(1): 
	    v = min_max(root,color); 
		break;
      case(2): 
	    v = negascout(root, numeric_limits<signed int>::min(), numeric_limits<signed int>::max(),color); 
	    break;
    }
  } else {
    for (int i = 0 ; i <= 32; i++){
      val[i] = root;
      root = root.move(color,PV[i]);
      color = !color;
    }
    switch (al) {
      case(0):
        for(int i = 32; i >= 0 ; i--){
          cout << "altura: " << 32 - i << endl; 
          v = alpha_beta_prunning(val[i], numeric_limits<signed int>::min(), numeric_limits<signed int>::max(),!color);
          color = !color; 
          cout << v << endl;
        }
        break;
      case(1): 
	    for(int i = 32; i >= 0 ; i--){
           cout << "altura: " << 32 - i << endl; 
           v = min_max(val[i],!color);
           color = !color; 
           cout << v << endl;
	    }
	    break;
      case(2):
	    for(int i = 32; i >= 0 ; i--){
           cout << "altura: " << 32 - i << endl; 
           v = negascout(val[i], numeric_limits<signed int>::min(), numeric_limits<signed int>::max(),!color);
           color = !color; 
           cout << v << endl;
	    }	  
	    break;
    }
  }
  return 0;
}