/**
 * @file Grid.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-29
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "Grid.hpp"
#include "Coordinates.hpp"
using namespace std;

Grid::Grid(int x, int y) : size_x(x), size_y(y)
{
    for (int row = 0; row < x; row++) {
        for (int col = 0; col < y; col++) {
            // cells.push_back(Cell(row,col));
            cells.push_back(0);
        }
    } 
}

Grid::~Grid()
{
}

Grid *Grid::Copy()
{
    Grid *new_grid = new Grid(size_x, size_y);

    for (int row = 0; row < size_x; row++) {
        for (int col = 0; col < size_y; col++) {
            double value = this->GetCellState(row, col);
            new_grid->SetCellState(row, col, value);
        }
    } 
    return new_grid;
}

int Grid::GetX() const
{
    return size_x;
}

int Grid::GetY() const
{
    return size_y;
}


double Grid::GetCellState(int row, int col) const
{
    return cells.at(size_y*row + col);
}
double Grid::GetMinState()
{
    return *min_element(cells.begin(), cells.end());

}
double Grid::GetMaxState()
{
    return *max_element(cells.begin(), cells.end());
}

void Grid::SetCellState(int row, int col, double value)
{
    cells.at(size_y*row + col) = value;
}


vector<Coordinates> Grid::get_neighbours(int row, int col)
{
    vector<Coordinates> tmp;

    if (row < 0 || col < 0 || row >= GetX() || col >= GetY())
        return tmp;

    if (col-1 >= 0) {
        if (row+1 < GetX()) tmp.push_back(Coordinates(row+1, col-1));
        tmp.push_back(Coordinates(row, col-1));
        if (row-1 >= 0) tmp.push_back(Coordinates(row-1, col-1));
    }

    if (col >= 0) {
        if (row+1 < GetX()) tmp.push_back(Coordinates(row+1, col));
        if (row-1 >= 0)     tmp.push_back(Coordinates(row-1, col));
    }

    if (col+1 < GetY()) {
        if (row+1 < GetX()) tmp.push_back(Coordinates(row+1, col+1));
        tmp.push_back(Coordinates(row, col+1));
        if (row-1 >= 0) tmp.push_back(Coordinates(row-1, col+1));
    }


    return tmp;
}
