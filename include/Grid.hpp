/**
 * @file Grid.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-29
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef GRID_HPP
#define GRID_HPP

// #include "//cell.hpp"
#include "Coordinates.hpp"
#include <vector>
#include <array>

using namespace std;

class Grid
{
    private:
        /* data */
        int size_x;
        int size_y;

        vector<double> cells;
    public:
        Grid(int x, int y);
        ~Grid();
        Grid* Copy();
        int GetX() const;
        int GetY() const;

        double GetCellState(int row, int col) const;
        double GetMinState();
        double GetMaxState();
        void SetCellState(int row, int col, double value);
        vector<Coordinates> get_neighbours(int row, int col);
};


#endif