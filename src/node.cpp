// Nodo de 15 puzzle
#include "node.h"

using namespace std;

bool node::is_goal()
{
#ifdef X_64
	return this->val == 0x123456789ABCDEF0;
#else
	return (this->val[0] == 0x12345678 && this->val[1] == 0x9ABCDEF0);
#endif
}
