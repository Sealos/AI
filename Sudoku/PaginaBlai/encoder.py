#!/usr/bin/python

import sys
import pprint

n = 0

#9*9*9 variables
def encode(puzzle):
	file_out = sys.argv[3]
	variables = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(n)]
	num = 0
	f = open(file_out, 'w')
	for i in range(n):
		for j in range(n):
			for num in range(n):
				val = n3_to_n(i, j, num)
				if (num == puzzle[i][j]):
					s = str(val) + " 0" + str(i) + " " + str(j) + " " + str(num) + " " + str(val) + "\n"
				else:
					s = "-" + str(val) + " 0" + str(i) + " " + str(j) + " " + str(num) + " " + str(val) + "\n"
				f.write(s)



def parse(puzzle):
	count = 0
	x = 0
	y = 0
	tablero = [[0 for _ in range(n)] for _ in range(n)]
	puzzle = puzzle.rstrip('\n')
	for char in puzzle:
		if (char != '.'):
			tablero[x][y] = int(char)
		count = count + 1
		x = count // n
		y = count % n
	pprint.pprint(tablero)
	encode(tablero)
	#add_fixed_closures()
	print()

def open_file(file):
	f = open(file)
	for line in f:
		if (len(line) > 1):
			parse(line)

def n_to_n3(v_number):
	num = v_number % n
	rest = v_number // n
	y = rest % n
	rest = rest // n
	x = rest
	return [x, y, num]

# (n x n x n) -> n
def n3_to_n(x, y, num):
	s2 = n * n
	s1 = n * s2

	return x*n*n + y*n + num

def main(argc = 0, argv = None):
	if (len(argv) != 4):
		exit(1)
	global n
	n = int(argv[1])
	file_in = argv[2]
	file_out = argv[3]
	open_file(file_in)

exit(main(len(sys.argv), sys.argv))
