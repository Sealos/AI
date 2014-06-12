#!/usr/bin/python

import sys
import pprint

n = 0
def n_to_n3(v_number):
	num = v_number % n
	rest = v_number // n
	y = rest % n
	rest = rest // n
	x = rest
	return [x, y, num]

def n3_to_n(x, y, num):
	return x*n*n + y*n + num

def print_sudoku(puzzle):
	print(len(puzzle))
	tablero = [[-1 for _ in range(n)] for _ in range(n)]
	for var in puzzle:
		l = n_to_n3(int(var) - 1)
		tablero[l[0]][l[1]] = l[2]
	pprint.pprint(tablero)

def open_file(file):
	f = open(file)
	first = f.readline()
	if (first == 'SAT\n'):
		res = f.readline().split()
		l = [i for i in res if i[0] != '-']
		print_sudoku(l[:-1])
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
