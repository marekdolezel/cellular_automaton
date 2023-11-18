/**
 * @file main.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-02
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip> // for setprecision

#ifdef OPENGL_FOUND
#include <GL/glut.h>
#endif

#include <getopt.h>

// 3rd party libraries
#include <cxxopts.hpp> // replacement for getopt.h

#include "Grid.hpp"
#include "Polluters.hpp"
#include "CellularAutomaton.hpp"
#include "render.hpp"


int EndOfSimulationTime = 0;
int Time = 0;

CellularAutomaton* ca;


// Options
template <typename T>
struct OptionWithArg {
    bool set;
    T value;
};

struct Option {
    bool set;
};

struct Options {
        Option graphical;
        Option console;
        OptionWithArg<std::string> inputConfigFile;
        OptionWithArg<std::string> outputResultsFile;
        OptionWithArg<int> endOfSimulationTime;
        OptionWithArg<int> xgridSize;
        OptionWithArg<int> ygridSize;
        OptionWithArg<double> delta;
} opts = {0};

template <typename T>
void printOptionWithArg(const OptionWithArg<T>& option) {
    if (option.set) {
        std::cout << option.value;
    } else {
        std::cout << "Not set";
    }

    std::cout << std::endl;
}

void printOptions(const Options& options) {
    std::cout << "Graphical: " << std::boolalpha << options.graphical.set << std::endl;
    std::cout << "Console: " << std::boolalpha << options.console.set << std::endl;

    std::cout << "Input Config File: ";
    printOptionWithArg(options.inputConfigFile);

    std::cout << "End of Simulation Time: ";
    printOptionWithArg(options.endOfSimulationTime);
}
// END: options


void consolePrintGrid(Grid* cellsGrid)
{
    std::cout << "<----Start of Grid at time " << Time << std::endl;
    
    std::cout << "\t";
    for (int row = 0; row < cellsGrid->GetY(); row++)
        std::cout << "\t\t" << row;
    std::cout << std::endl;

    for (int row = 0; row < cellsGrid->GetX(); row++) {
            cout << "\t" << row;
            for (int col = 0; col < cellsGrid->GetY(); col++) {
                std::cout << std::fixed << setprecision(4) << "\t\t" << cellsGrid->GetCellState(row, col);
                
            }
            std::cout << std::endl;
    }
    std::cout << "MaxValueInCell " << ca->GetMaxValueInCell() << std::endl;
    std::cout << "^----End of Grid at time " << Time << endl << std::endl;
}



void runSimulationLoop(void)
{
   ca->InitPermutations();
   while (Time < opts.endOfSimulationTime.value) {
        #ifdef OPENGL_FOUND
        if (opts.graphical.set)
            openGL_PrintGrid(ca->GetGrid());
        if (opts.console.set)
            consolePrintGrid(ca->GetGrid());
        #else
        consolePrintGrid(ca->GetGrid());
        #endif
        ca->Evolve();
        Time++;
    }
}

int main(int argc, char* argv[])
{
    int rc = 0;

    cxxopts::Options options("cellular_automaton", " - command line options");
    options.add_options()
        #ifdef OPENGL_FOUND
        ("g, graphical", "Enable graphical mode", cxxopts::value<bool>(opts.graphical.set))
        ("c, console", "Enable console mode", cxxopts::value<bool>(opts.console.set))
        #endif
        ("x, xgrid", "x size of the grid", cxxopts::value<int>(opts.xgridSize.value))
        ("y, ygrid", "y size of the grid", cxxopts::value<int>(opts.ygridSize.value))
        ("d, delta", "delta parameter", cxxopts::value<double>(opts.delta.value))
        ("t, time", "End of simulation time", cxxopts::value<int>(opts.endOfSimulationTime.value))
        ("i, input_file", "Simulation configuration file", cxxopts::value<std::string>(opts.inputConfigFile.value))
        ("o, output_file", "Simulation configuration file", cxxopts::value<std::string>(opts.outputResultsFile.value))

        ("h,help", "");

    try {
        auto result = options.parse(argc, argv);

        // Set recognized options
        opts.xgridSize.set = result.count("xgrid")  > 0 ? true : false;
        opts.ygridSize.set = result.count("ygrid")  > 0 ? true : false;
        opts.delta.set = result.count("delta") > 0 ? true : false;
        opts.inputConfigFile.set = result.count("input_file")  > 0 ? true : false;
        opts.outputResultsFile.set = result.count("output_file")  > 0 ? true : false;
        opts.endOfSimulationTime.set = result.count("time")  > 0 ? true : false;
        opts.graphical.set = result.count("graphical")  > 0 ? true : false;
        opts.console.set = result.count("console")  > 0 ? true : false;

        // printOptions(opts);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }


        // CHECK options
        bool printUsageAndExit = false;

        // the grid size x and y are required arguments
        if (!opts.xgridSize.set || !opts.ygridSize.set) { 
            std::cerr << "Error: grid size x,y must be set with options -x -y." << std::endl;
            printUsageAndExit = true;
        }

        // Delta argument is required
        if (!opts.delta.set) {
            std::cerr << "Error: Delta arugment must be set with -d option." << std::endl;
            printUsageAndExit = true;
        }

        // Simulation configuration file is required argument
        if (!opts.inputConfigFile.set) { 
            std::cerr << "Error: No simulation configuration file was specified. Provide file with -i option." << std::endl;
            printUsageAndExit = true;
        }

        // Simulation configuration file is required argument
        if (!opts.outputResultsFile.set) {
            std::cerr << "Error: No output file was specified. Provide file with -o option." << std::endl;
            printUsageAndExit = true;
        }

        // Simulation time is required argument 
        if (!opts.endOfSimulationTime.set) {
            std::cerr << "Error: Simulation time must be set with -t option." << std::endl;
            printUsageAndExit = true;
        }

        if (printUsageAndExit) {
            std::cout << options.help() << std::endl;
            return -1;
        }
        // END: CHECK options

        try {
            ca = new CellularAutomaton(opts.xgridSize.value, opts.ygridSize.value, opts.delta.value, opts.inputConfigFile.value, opts.outputResultsFile.value);
        } catch (const std::exception& e) {
            // Catch the exception and print the error message
            std::cout << "Caught exception: " << e.what() << std::endl;
            return 1;
        }
        if (rc != 0) {
            cout << "The configuration file is invalid, or (x||y||delta) are out of bands." << endl;
            return  1;
        }

        if (opts.graphical.set) {
            #ifdef OPENGL_FOUND
            render_init(argc, argv);
            #endif
        }
        else
            runSimulationLoop();

        delete ca;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }

    
}