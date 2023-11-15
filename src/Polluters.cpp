/**
 * @file Polluters.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-30
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include "Polluters.hpp"
#include "Polluter.hpp"

Polluters::Polluters() {}
Polluters::~Polluters() {}

void Polluters::AddPolluter(int row, int col, double pollutionAmount)
{
    Polluters_arr.push_back(Polluter(row, col, pollutionAmount));
}

double Polluters::GetPollutionAmount(int row, int col)
{
    for (vector<Polluter>::iterator it = Polluters_arr.begin() ; it != Polluters_arr.end(); it++) {
        if ( it->getX() == row && it->getY() == col)
            return it->GetPollutionAmount(); 
    }

    return -1;

}

void Polluters::UpdatePollutionAmount(int row, int col, double newPollution)
{
    for (vector<Polluter>::iterator it = Polluters_arr.begin() ; it != Polluters_arr.end(); it++) {
        if ( it->getX() == row && it->getY() == col)
            return it->UpdatePollutionAmount(newPollution); 
    }
}

