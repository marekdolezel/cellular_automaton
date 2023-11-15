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

#include <GL/glut.h>

#include <getopt.h>

// 3rd party libraries
#include <INIReader.hpp> // External INI parser in INIreader directory
#include <cxxopts.hpp> // replacement for getopt.h

#include "Grid.hpp"
#include "Polluters.hpp"
#include "CellularAutomaton.hpp"
#include "render.hpp"


int EndOfSimulationTime = 0;
int Time = 0;

CellularAutomaton* ca;

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
        OptionWithArg<int> endOfSimulationTime;
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


void consolePrintGrid(const Grid* cellsGrid)
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
       
        if (opts.graphical.set)
            openGL_PrintGrid(ca->GetGrid());
        if (opts.console.set)
            consolePrintGrid(ca->GetGrid());
        ca->Evolve(Time);
       
        // ca->SwapGrids();
        // swap grids here?
        Time++;
    }
}

void usage()
{
    std::cerr
        << std::endl
        << "Usage:" << std::endl  
        << "simulation: [-f simulation file] -g [-t simulationDuration]" << std::endl
        << "simulation: [-f simulation file] [-t simulationDuration]" << std::endl
        << "simulation: [-f simulation file] [-t simulationDuration]" << std::endl << std::endl

        << "You must specify a simulation file with required parameters (-g or -c (implicit -c))" << std::endl
        << "This is an example of a required simulation file:" << std::endl << std::endl
        << "\t[Grid]" << std::endl
        << "\tx = 10" << std::endl
        << "\ty = 10" << std::endl
        << "\tdelta = 0.1" << std::endl
        << "\t;optional sections" << std::endl << std::endl
        << "\t[Polluters]" << std::endl
        << "\tcount = 2" << std::endl << std::endl

        << "\t[Polluter1]" << std::endl
        << "\tx = 1; x coordinate of Polluter 1" << std::endl
        << "\ty = 1; y coordinate of Polluter 1" << std::endl
        << "\ta = 10; amount of pollution introduced to cell occupied by Polluter 1" << std::endl << std::endl

        << "\t[Polluter2]" << std::endl
        << "\tx = 1; x coordinate of Polluter 2" << std::endl
        << "\ty = 1; y coordinate of Polluter 2" << std::endl
        << "\ta = 10; amount of pollution introduced to cell occupied by Polluter 2" << std::endl

        << "double max: " << std::numeric_limits<double>::max() << std::endl;
}


int main(int argc, char* argv[])
{
    int rc = 0;

    cxxopts::Options options("MyProgram", " - command line options");
    options.add_options()
        ("g, graphical", "Enable graphical mode", cxxopts::value<bool>(opts.graphical.set))
        ("c, console", "Enable console mode", cxxopts::value<bool>(opts.console.set))
        ("t, time", "End of simulation time", cxxopts::value<int>(opts.endOfSimulationTime.value))
        ("f, file", "Simulation configuration file", cxxopts::value<std::string>(opts.inputConfigFile.value))
        ("h,help", "Print usage");

    try {
        auto result = options.parse(argc, argv);

        // Set recognized options
        opts.inputConfigFile.set = result.count("file")  > 0 ? true : false;
        opts.endOfSimulationTime.set = result.count("time")  > 0 ? true : false;
        opts.graphical.set = result.count("graphical")  > 0 ? true : false;
        opts.console.set = result.count("console")  > 0 ? true : false;

        printOptions(opts);

        // CHECK options
        // Simulation configuration file is required 
        if (!opts.inputConfigFile.set) {
            std::cerr << "Error: No simulation configuration file was entered. Provide file with -f option." << std::endl;
            usage();
            return -1;
        }

        // Simulation time must be set 
        if (!opts.endOfSimulationTime.set) {
            std::cerr << "Error: Simulation time must be set with -t option." << std::endl;
            usage();
            return -1;
        }
        // END: CHECK options

        ca = new CellularAutomaton(opts.inputConfigFile.value);

        // rc = ca->LoadSimulationFromFile(opts.inputConfigFile.value);
        if (rc != 0) {
            cout << "The configuration file is invalid, or (x||y||delta) are out of bands." << endl;
            return  1;
        }

        if (opts.graphical.set) {
            render_init(argc, argv);
        }
        else
            runSimulationLoop();

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }

    
}