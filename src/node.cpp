// Nodo de 15 puzzle


bool node::is_goal()
{
	return rep.val[0] == 0x12345678 && rep.val[1] == 0x9ABCDEF0;
}

