#!/bin/bash

# Helper functions:

# Function to check if a command exists
check_command_exists() {
    if command -v "$1" &> /dev/null; then
        return 0;
    else
        return 1;
    fi
}



# Set the default executable
DEFAULT_EXECUTABLE=./build/cellular_automaton
CLEAN_UP=0

# Colors for test results
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Check if an argument is provided, use it as the executable, otherwise use the default
if [ $# -eq 1 ]; then
    EXECUTABLE=$1
else
    EXECUTABLE=$DEFAULT_EXECUTABLE
fi

# Check if the executable exists
if [ -x "$EXECUTABLE" ]; then
    echo "Executable found: $EXECUTABLE"
else
    CLEAN_UP=1
    EXECUTABLE=$DEFAULT_EXECUTABLE
    echo "Executable not found. Building..."
    mkdir -p build
    cd build || exit
    cmake .. #>>/dev/null
    make #>>/dev/null
    cd .. || exit
fi

# Check again if the executable exists after the build
if [ ! -x "$EXECUTABLE" ]; then
    echo "Failed to build the executable. Exiting."
    exit 1
fi

# echo "Running executable ${EXECUTABLE}"

# Iterate through all CSV files starting with "experiment"
for experiment_file in experiment*.csv; do
    if [ -f "$experiment_file" ]; then
        # Extract x, y, and d values from the filename
        filename=$(basename "$experiment_file")
        filename_without_extension="${filename%.csv}"  # Remove the .csv extension
        IFS='_' read -r -a params <<< "$filename_without_extension" # Split filename by underscores
        experiment_id="${params[0]#experiment}"  # Remove "experiment" prefix
        x="${params[1]}"
        y="${params[2]}"
        t="${params[3]}"
        d="${params[4]/p/.}"  # Replace 'p' with a decimal point
        
        # Formulate output filename for results
        results_file="${filename_without_extension}_results.csv"

        # Run Executable with specified options for each experiment file
        temp_file=$(mktemp)
        ${EXECUTABLE} -x "$x" -y "$y" -d "$d" -t "$t" -i "$experiment_file" -o "$results_file" 2>&1 $temp_file
        ret_code=$?
        
        echo -e "Experiment $experiment_id: "
        echo -e "\tcommand: ${EXECUTABLE} -x "$x" -y "$y" -d "$d" -t "$t" -i "$experiment_file" -o "$results_file""
        echo -e "\treturn code: ${ret_code}"
        echo -e "\tprogram output: ** $(cat $temp_file) ** "
        # Check if the execution was successful before plotting
        
        if [ $ret_code -eq 0 ]; then
            echo -ne "\tstatus: " echo -e "${GREEN}OK${NC}"
            EXPERIMENT_RESULT_CSV="${results_file}"
            if check_command_exists "gnuplot"; then
                gnuplot -p -e "filename='${EXPERIMENT_RESULT_CSV}';" gnuplot.gnuplot
            fi
        else
            echo -e "\tStatus: " echo -e "${RED}FAILED${NC}"
        fi
    fi
done

if [ $CLEAN_UP -eq 1 ]; then
    echo "Performing cleanup of build directory..."
    rm -rf build
fi