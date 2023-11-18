/**
 * @file CellularAutomaton.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-02
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef CELLULAR_AUTOMATON_HPP
#define CELLULAR_AUTOMATON_HPP

#include <string>

#include "Grid.hpp"
#include "WindField.hpp"
#include "Polluters.hpp"
#include "Statistics.hpp"

using namespace std;

class CellularAutomaton
{
private:
    /* data */
    Statistics *stat;

    double delta;
    Grid *cellsGrid;
    Grid *cellsGrid_t1;
    WindField *windSpeed;
    WindField *windMultipliers;
    Polluters *polluters;
    double MaxValue;
public:
    CellularAutomaton(int x, int y, double delta, string simulationConfigFile, string outputFile);
    ~CellularAutomaton();
    int LoadSimulationFromFile(string simulationCfgFile);
    void InitPermutations();
    void Evolve();
    void SwapGrids();
    Grid *GetGrid();
    double GetMaxValueInCell();
    void SetMaxValueInCell(double value);
};

#endif