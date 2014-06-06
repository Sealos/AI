#!/bin/bash

while read line; do
    ./sudoku_solver.sh $line $2
done < $1
