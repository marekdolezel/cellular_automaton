/**
 * @file Polluters.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-30
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef POLLUTERS_HPP
#define POLLUTERS_HPP
#include <vector>
#include "Polluter.hpp"

using namespace std;

class Polluters
{
private:
    /* data */
    vector<Polluter> Polluters_arr;
public:
    Polluters();
    ~Polluters();
    void AddPolluter(int row, int col, double pollutionAmount);
    double GetPollutionAmount(int row, int col);
    void UpdatePollutionAmount(int row, int col, double newPollution);
};

#endif