#!/bin/bash

# Set the default executable
DEFAULT_EXECUTABLE=./build/simulation

# Check if an argument is provided, use it as the executable, otherwise use the default
if [ $# -eq 1 ]; then
    EXECUTABLE=$1
else
    EXECUTABLE=$DEFAULT_EXECUTABLE
fi

echo "Running executable ${EXECUTABLE}"

EXPERIMENT1_RESULT_CSV=experiment1stat.csv
EXPERIMENT2_RESULT_CSV=experiment2stat.csv

${EXECUTABLE} -f experiment1 -t 300 && gnuplot -p -e "filename='${EXPERIMENT1_RESULT_CSV}';" gnuplot.gnuplot

${EXECUTABLE} -f experiment2 -t 300 && gnuplot -p -e "filename='${EXPERIMENT2_RESULT_CSV}';" gnuplot.gnuplot
