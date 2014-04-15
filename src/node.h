// Nodo de 15 puzzle
#ifndef NODE_H
#define NODE_H

#def POS_0_8	0xF0000000
#def POS_1_9	0x0F000000
#def POS_2_10	0x00F00000
#def POS_3_11	0x000F0000
#def POS_4_12	0x0000F000
#def POS_5_13	0x00000F00
#def POS_6_14	0x000000F0
#def POS_7_15	0x0000000F

class node
{
	struct puzzle_rep
	{
		int val[2];
	} rep;

	bool is_goal();
}

#endif /* NODE_H */