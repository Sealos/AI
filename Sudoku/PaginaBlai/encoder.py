#!/usr/bin/python

import sys
import pprint

n = 0

#9*9*9 variables
def encode(puzzle, f):
	variables = [[[0 for _ in range(n)] for _ in range(n)] for _ in range(n)]
	num = 0
	for i in range(n):
		for j in range(n):
			for num in range(n):
				val = n3_to_n(i, j, num) + 1
				if (num == puzzle[i][j]):
					s = str(val) + " 0\n"
				else:
					s = "-" + str(val) + " 0\n"
				f.write(s)

def clo_one_number_per_pos(f):
	s = ""
	dif = ""
	# Al menos 1
	for i in range(n):
		for j in range(n):
			for num in range(n):
				var = n3_to_n(i, j, num) + 1
				for n_num in range(num, n):
					n_var = n3_to_n(i, j, n_num) + 1
					if (var != n_var):
						dif = dif + "-" + str(var) + " -" + str(n_var) + " 0\n"
				s = s + str(var) + " "
			s = s + "0\n"
			f.write(s)
			f.write(dif)
			s = ""
			dif = ""


def clo_one_number_per_grid(f):
	for i in range(n):
		for j in range(n):

def clo_one_number_per_row(f):
	return None

def clo_one_number_per_collum(f):
	return None


def clo_fixed(f):
	clo_one_number_per_pos(f)
	clo_one_number_per_grid(f)
	clo_one_number_per_row(f)
	clo_one_number_per_collum(f)

def parse(puzzle):
	count = 0
	x = 0
	y = 0
	file_out = sys.argv[3]
	f = open(file_out, 'w')
	tablero = [[0 for _ in range(n)] for _ in range(n)]
	puzzle = puzzle.rstrip('\n')
	for char in puzzle:
		if (char != '.'):
			tablero[x][y] = int(char)
		count = count + 1
		x = count // n
		y = count % n
	pprint.pprint(tablero)
	encode(tablero, f)
	clo_fixed(f)
	f.close()
	print()

def open_file(file):
	f = open(file)
	for line in f:
		if (len(line) > 1):
			parse(line)
	f.close()


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

def main(argc = 0, argv = None):	
	if (len(argv) != 4):
		exit(1)
	global n
	n = int(argv[1])
	file_in = argv[2]
	file_out = argv[3]
	open_file(file_in)

exit(main(len(sys.argv), sys.argv))
