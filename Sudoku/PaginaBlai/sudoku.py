#!/usr/bin/python3

import sys
from os import remove
from tempfile import NamedTemporaryFile
from subprocess import call

def fix_me():
	print("sudoku.py <n> <in> <out> [sat_solver=minisat]")


def execute(f_in, f_out):
	f_in = open(f_in)
	f = open(f_out, 'w')
	for line in f_in:
		if (len(line) > 1):
			solve(line, f)
	f.close()
	f_in.close()


def get_time(file):
	for line in file:
		if (line[0] == 'C'):
			return line.split()[3]

def solve(puzzle, f_out):
	temp_a = open('tmp', 'w')
	temp_a.write(puzzle)
	temp_a.close()
	temp_c = open('tmp4', 'w')
	call(["./encoder.py", "9", 'tmp', "tmp2"])
	call(["./minisat", "tmp2", "tmp3"], stdout=temp_c)
	temp_c.close()
	temp_c = open('tmp4', 'r+')
	t = get_time(temp_c)
	temp_c.close()
	remove("./tmp4")
	temp_c = open('tmp4', 'w')
	call(["./decoder.py", "9", "tmp3"], stdout=temp_c)
	temp_d = open('tmp4')

	l = temp_d.readline()
	temp_d.close()
	remove("./tmp")
	remove("./tmp2")
	remove("./tmp3")
	remove("./tmp4")
	f_out.write(puzzle.rstrip('\n') + "\t" + l + "\tt: " + t + "s" + "\t" + "\n")

def main(argc = 0, argv = None):
	if (argc < 4):
		fix_me()
		exit(1)

	if (argc == 4):
		argv.append("minisat")

	execute(argv[2], argv[3])

exit(main(len(sys.argv), sys.argv))
