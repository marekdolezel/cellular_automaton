/**
 * @file WindField.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-30
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include <vector>
#include "WindField.hpp"

using namespace std;

WindField::WindField(int x, int y) : size_x(x), size_y(y)
{
    for (int row = 0; row < x; row++) {
        for (int col = 0; col < y; col++) {
            NorthSouth.push_back(0.0);
            EastWest.push_back(0.0);
        }
    } 
}

WindField::~WindField() {}

void WindField::SetEastWestWind(double value)
{
    fill(EastWest.begin(), EastWest.end(), value);
}

void WindField::SetNorthSouthWind(double value)
{
    fill(NorthSouth.begin(), NorthSouth.end(), value);
}

void WindField::SetNorthSouth(int row, int col, double value)
{
    NorthSouth[size_y*row + col] = value;
}

void WindField::SetEastWest(int row, int col, double value)
{
    EastWest[size_y*row + col] = value;
}

double WindField::GetNorthSouth(int row, int col) 
{
    return NorthSouth.at(size_y*row + col);
}

double WindField::GetEastWest(int row, int col) 
{
    return EastWest.at(size_y*row + col);
}