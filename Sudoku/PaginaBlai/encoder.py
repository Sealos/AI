#!/usr/bin/python

import sys
import pprint

n = 0

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
	print()

def open_file(file):
	f = open(file)
	for line in f:
		parse(line)

def n_to_n3(v_number):
	x = v_number % n
	rest = v_number // n
	y = rest % n
	rest = rest // n
	num = rest
	return [x, y, num]

# (n x n x n) -> n
def n3_to_n(x, y, num):
	s2 = n * n
	s1 = n * s2

	return x + y * n + num * n * n

def main(argc = 0, argv = None):
	if (len(argv) != 4):
		exit(1)
	print(str(argc))
	global n
	n = int(argv[1])
	file_in = argv[2]
	file_out = argv[3]
	open_file(file_in)

exit(main(len(sys.argv), sys.argv))