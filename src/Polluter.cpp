/**
 * @file Polluter.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-29
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include "Polluter.hpp"

Polluter::Polluter(int x, int y) : X(x), Y(y) {}

Polluter::Polluter(int x, int y, double pollution) : Pollution(pollution), X(x), Y(y) {}

Polluter::~Polluter() {}

double Polluter::GetPollutionAmount()
{
    return Pollution;
}

void Polluter::UpdatePollutionAmount(double newPollution)
{
    Pollution = newPollution;
}

int Polluter::getX()
{
    return X;
}
int Polluter::getY()
{
    return Y;
}

