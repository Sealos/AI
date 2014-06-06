#!/bin/bash

ENCODER=~/ci5437-proyecto3/static_encoder
DECODER=~/ci5437-proyecto3/decoder
SAT_SOLVER=glucose_2.1/
CNF=~/.sudoku.temporal
# Corremos el generador de dimacs
$ENCODER $1 > $CNF

# Corremos el SAT solver
cd $SAT_SOLVER
./glucose.sh $CNF | sed '/^$/d' | sed '/^c/d' | $DECODER $2

# rm $CNF
