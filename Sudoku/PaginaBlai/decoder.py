#!/usr/bin/python

import sys

n = 0
tablero = None
variables = None

def n_to_n3(v_number):
	num = v_number % n
	rest = v_number // n
	y = rest % n
	rest = rest // n
	x = rest
	return [x, y, num]

def n3_to_n(x, y, num):
	s2 = n * n
	s1 = n * s2
	return x*n*n + y*n + num


def main(argv = None):
	if (len(sys.argv) > 0):
		global n
		n = int(sys.argv[1])
	else:
		exit(1)



#ran = range(0, n)

main(sys.argv)

#tablero = [[[0 for _ in range(n)] for _ in range(n)]
#variables = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(n)]
