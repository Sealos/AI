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

def open_file(file):
	f = open(file)
	first = f.readline()
	if (first == 'SAT\n'):
		for line in f:
			print(line)
	else:
		print("UNSAT")	
	f.close()

def main(argv = None):
	if (len(argv) == 4):
		global n
		n = int(sys.argv[1])
		file_in = argv[2]
		file_out = argv[3]
		open_file(file_in)
	else:
		exit(1)
	
#ran = range(0, n)

main(sys.argv)

#tablero = [[[0 for _ in range(n)] for _ in range(n)]
#variables = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(n)]
