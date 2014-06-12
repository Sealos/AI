#!/usr/bin/python

import sys
import pprint

n = 0

def primes(n):
	primfac = []
	d = 2
	while d*d <= n:
		while (n % d) == 0:
			primfac.append(d)  # supposing you want multiple factors repeated
			n /= d
		d += 1
	if (n > 1):
		primfac.append(n)
	return primfac


#9*9*9 variables
def encode(puzzle, f):
	pprint.pprint(puzzle)
	num = 0
	for i in range(n):
		for j in range(n):
			for num in range(n):
				val = n3_to_n(i, j, num) + 1
				if (num == puzzle[i][j] - 1):
					s = str(val) + " 0\n"
					f.write(s)


def clo_one_number_per_pos(f):
	s = ""
	dif = ""
	for i in range(n):
		for j in range(n):
			for num in range(n):
				var = n3_to_n(i, j, num) + 1
				for n_num in range(num + 1, n):
					n_var = n3_to_n(i, j, n_num) + 1
					dif = dif + "-" + str(var) + " -" + str(n_var) + " 0\n"
				s = s + str(var) + " "
			s = s + "0\n"
			f.write(s)
			f.write(dif)
			s = ""
			dif = ""

def clo_one_number_per_grid(f):
	clo_one_number_per_grid_1(f)
	clo_one_number_per_grid_2(f)
	clo_one_number_per_grid_3(f)

def clo_one_number_per_grid_1(f):
	s = ""
	for num in range(n):
		for i in range(3):
			for j in range(3):
				for x in range(3):
					for y in range(3):
						var = n3_to_n(3*i + x, 3*j + y, num) + 1
						for k in range(y + 1, 3):
							n_var = n3_to_n(3*i + x, 3*j + k, num) + 1
							s = "-" + str(var) + " -" + str(n_var) + " 0\n"
							f.write(s)


def clo_one_number_per_grid_2(f):
	s = ""
	for num in range(n):
		for i in range(3):
			for j in range(3):
				for x in range(3):
					for y in range(3):
						var = n3_to_n(3*i + x, 3*j + y, num) + 1
						for k in range(x + 1, 3):
							for l in range(3):
								n_var = n3_to_n(3*i + k, 3*j + l, num) + 1
								s = "-" + str(var) + " -" + str(n_var) + " 0\n"
								f.write(s)

def clo_one_number_per_grid_3(f):
	s = ""
	for i in range(3):
		for j in range(3):
			for x in range(3):
				for y in range(3):
					for num in range(n):
						var = n3_to_n(3*i + x, 3*j + y, num) + 1
						s = s + str(var) + " "
					s = s + "0\n"
					f.write(s)
					s = ""


def clo_one_number_per_collum(f):
	s = ""
	dif = ""
	for j in range(n):
		for num in range(n):
			for i in range(n):
				var = n3_to_n(i, j, num) + 1
				for n_i in range(i + 1, n):
					n_var = n3_to_n(n_i, j, num) + 1
					dif = dif + "-" + str(var) + " -" + str(n_var) + " 0\n"
				s = s + str(var) + " "
			s = s + "0\n"
			f.write(s)
			f.write(dif)
			s = ""
			dif = ""

def clo_one_number_per_row(f):
	s = ""
	dif = ""
	for i in range(n):
		for num in range(n):
			for j in range(n):
				var = n3_to_n(i, j, num) + 1
				for n_j in range(j + 1, n):
					n_var = n3_to_n(i, n_j, num) + 1
					dif = dif + "-" + str(var) + " -" + str(n_var) + " 0\n"
				s = s + str(var) + " "
			s = s + "0\n"
			f.write(s)
			f.write(dif)
			s = ""
			dif = ""

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

def n3_to_n(x, y, num):
	return x*n*n + y*n + num

def main(argc = 0, argv = None):
	if (len(argv) != 4):
		exit(1)
	global n
	n = int(argv[1])
	file_in = argv[2]
	file_out = argv[3]
	open_file(file_in)

main(len(sys.argv), sys.argv)
