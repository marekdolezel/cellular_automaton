/**
 * @file Coordinates.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-01
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include "Coordinates.hpp"

Coordinates::Coordinates(int x, int y) :X(x), Y(y)
{
}

Coordinates::~Coordinates()
{
}

int Coordinates::GetX() { return X; }
int Coordinates::GetY() { return Y; }
