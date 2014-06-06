#!/bin/bash

while read line; do
    ./sudoku_solver_static.sh $line $2
done < $1
