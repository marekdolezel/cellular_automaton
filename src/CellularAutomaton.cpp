/**
 * @file CellularAutomaton.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-02
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>        // std::time
#include <algorithm>    // std::random_shuffle

#include "Statistics.hpp"
#include "CellularAutomaton.hpp"
#include "Grid.hpp"
#include "WindField.hpp"
#include "Polluters.hpp"

using namespace std;

extern int Time;

CellularAutomaton::CellularAutomaton(int x, int y, double delta, string simulationConfigFile, string outputFile) 
{
    cellsGrid = new Grid(x, y);

    windSpeed = new WindField(x, y);
    windMultipliers = new WindField(x, y);
    polluters = new Polluters();
    
    // create 2 column csv file 'time' 'concentrationOfSystem'
    stat = new Statistics(2, outputFile);

    stat->SetColName(0, "time");
    stat->SetColName(1, "concentrationOfSystem");

    int ret_code = this->LoadSimulationFromFile(simulationConfigFile); // TODO: check for return value
}

CellularAutomaton::~CellularAutomaton()
{
    stat->DumpToFile();
    delete stat;
    delete cellsGrid;
    delete windMultipliers;
    delete windSpeed;
    delete polluters;
}

int CellularAutomaton::LoadSimulationFromFile(string simulationCfgFile)
{
    ifstream configurationStream(simulationCfgFile);
    if (!configurationStream.is_open())
        throw std::runtime_error("File not found.");

    while(!configurationStream.eof()) {
        int pol_x;
        int pol_y;
        int pol_a;
        configurationStream >> pol_x >> pol_y >> pol_a;

        // if (configurationStream.fail()) {
            // return -1;
        // }

        // coordinates cannot be negative or equal or greater than gridX, gridY
        if (pol_x < 0 || pol_y < 0 || pol_a < 0 || pol_x >= cellsGrid->GetX() || pol_y >= cellsGrid->GetY()) {
            throw std::runtime_error("Invalid configuration file.");
        }
        polluters->AddPolluter(pol_x, pol_y, pol_a);
    }

    // int numof_explicit_cells = reader.GetInteger("ExplicitCells", "count", 0);
    // for (int i = 0; i < numof_explicit_cells; i++) {
    //     string explicitcell_ininame = "ExplicitCell" + to_string(i+1);
    //     int ExplicitCellX = reader.GetInteger(explicitcell_ininame, "x", -1);
    //     int ExplicitCellY = reader.GetInteger(explicitcell_ininame, "y", -1);
    //     int ExplicitCellA = reader.GetReal(explicitcell_ininame, "a", -1);

    //     if (ExplicitCellX < 0 || ExplicitCellY < 0 || ExplicitCellA < 0)
    //         return -2;  // we need to destroy some objects

    //     if (ExplicitCellX < cellsGrid->GetX() && ExplicitCellY < cellsGrid->GetY())
    //         cellsGrid->SetCellState(ExplicitCellX, ExplicitCellY, ExplicitCellA);
    //     else
    //         return -3; 
    // }

    return 0;
}


std::vector<int> permutations;
std::vector<int> y_coord;
void CellularAutomaton::InitPermutations()
{
    std::srand ( unsigned ( std::time(0) ) );

    for (int i=0; i<(cellsGrid->GetX()*cellsGrid->GetY()); ++i) permutations.push_back(i); // 1 2 3 4 5 6 7 8 9


    windSpeed->SetNorthSouthWind(2.0);
}
void CellularAutomaton::Evolve()
{
    double current_cell_state = 0.0;
    double new_cell_state = 0.0;
    double curr_neighbour_state = 0.0;
    double new_neighbour_state = 0.0;
    double pollution_amount = 0.0;
    double sums = 0.0;
    

    vector<int> permutations_copy = permutations;
    std::random_shuffle ( permutations_copy.begin(), permutations_copy.end() );

    // cellsGrid_t1 = cellsGrid->Copy(); // create copy of current Grid
    for (int iteration = 0; iteration < (cellsGrid->GetX()*cellsGrid->GetY()); iteration++) {

        int lin_idx = permutations_copy[iteration];

        int row = lin_idx % cellsGrid->GetY();
        int col = lin_idx / cellsGrid->GetY();

        // cout << "row, col(" << row << col << ")" << endl;
        current_cell_state = cellsGrid->GetCellState(row, col);
        sums += current_cell_state;
        /* Apply molecular diffusion 
            Rule 1.     P(r,c,t+1) = P(r,c,t) - delta*P(r,c,t) 
        */
        // TODO: fix rule1

        new_cell_state = current_cell_state - delta*current_cell_state;  
        if (current_cell_state > 0) {
            // double state = cellsGrid_t1->GetCellState(row, col); 
            cellsGrid->SetCellState(row, col, new_cell_state);  //t1
        }


        /* For all neighbours C(p,q) of cell C(r,c) we apply the following rules
            Rule 2.     P(p,q,t+1) = P(p,q,t) + 0.125*(1-delta)*P(r,c,t)
            */
        vector <Coordinates> neighbours = cellsGrid->get_neighbours(row, col);
        // cout << "neighbours check " << neighbours.size() << endl;
        if (current_cell_state != 0) {

            for (vector<Coordinates>::iterator neighbour = neighbours.begin(); neighbour != neighbours.end(); neighbour++) {
                // cout << "neighbour " << neighbour->GetX() << neighbour->GetY() << endl;
                curr_neighbour_state = cellsGrid->GetCellState(neighbour->GetX(), neighbour->GetY());
                new_neighbour_state = curr_neighbour_state + 0.125*(delta)*current_cell_state;
                cellsGrid->SetCellState(neighbour->GetX(), neighbour->GetY(), new_neighbour_state); //t1
            } 
                
                double w;
                //WN+ north

                double WN = windSpeed->GetNorthSouth(row,col);
                double WE = windSpeed->GetNorthSouth(row,col);
                double new_neighbour_state;
                if(WN > 0) {
                    if (row-1>=0 ) {
                        double curr_neighour_state = cellsGrid->GetCellState(row-1, col);
                        double new_neighbour_state = curr_neighbour_state + WN*current_cell_state;
                    }
                    else {

                    }
                }
        }

        /*
            w= wind WindNorthSouth or WindEastWest
            b=barrier
            Rule 3. P(p,q,t+1) = P(p,q,t) + w*b*P(r,c,t)

            WN+ North 
            Wn- south

            WE+ east
            wE- west
        */


        


        /* Source (Polluter) introduces pollution to its cell at each timestep 
            Rule 4.     P(r,c,t+1) = P(r,c,t) + G(sj, t)
        */
        pollution_amount = polluters->GetPollutionAmount(row, col);
        new_cell_state = current_cell_state + pollution_amount;

        if (pollution_amount != -1.0)
            cellsGrid->SetCellState(row, col, new_cell_state); //t1
        
        double maxValue = GetMaxValueInCell();
        if (current_cell_state > maxValue)
            SetMaxValueInCell(current_cell_state);

        
    }

    stat->AddData(0, Time);
    stat->AddData(1, sums);

    //cout << "SUMs: = " << sums << endl;

}

void CellularAutomaton::SwapGrids()
{
    Grid *new_Grid = cellsGrid_t1;
    Grid *new_Grid_t1 = cellsGrid;

    cellsGrid = new_Grid;
    cellsGrid_t1 = new_Grid_t1;
}

Grid *CellularAutomaton::GetGrid()
{
    return cellsGrid;
}

double CellularAutomaton::GetMaxValueInCell()
{
    return MaxValue;
}
void CellularAutomaton::SetMaxValueInCell(double value)
{
    MaxValue = value;
}