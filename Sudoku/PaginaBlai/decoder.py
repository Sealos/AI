#!/usr/bin/python3

import sys

n = 0
def n_to_n3(v_number):
	num = v_number % n
	rest = v_number // n
	y = rest % n
	rest = rest // n
	x = rest
	return [x, y, num]

def print_sudoku(puzzle):
	tablero = [[-1 for _ in range(n)] for _ in range(n)]
	for var in puzzle:
		l = n_to_n3(int(var) - 1)
		tablero[l[0]][l[1]] = l[2] + 1

	for i in range(n):
		for j in range(n):
			print(str(tablero[i][j]), end = "")

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
	if (len(argv) == 3):
		global n
		n = int(sys.argv[1])
		file_in = argv[2]
		open_file(file_in)
	else:
		exit(1)

main(sys.argv)
