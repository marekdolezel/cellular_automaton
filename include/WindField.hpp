/**
 * @file WindField.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-30
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef WIND_FIELD_HPP
#define WIND_FIELD_HPP

#include <vector>

using namespace std;
class WindField
{
private:
    /* data */
    int size_x;
    int size_y;

    vector<double> NorthSouth;
    vector<double> EastWest;
public:
    WindField(int size_x, int size_y);
    ~WindField();

    void SetEastWestWind(double value);
    void SetNorthSouthWind(double value);
    
    void SetNorthSouth(int row, int col, double value);
    void SetEastWest(int row, int col, double value);

    double GetNorthSouth(int row, int col);
    double GetEastWest(int row, int col);
};


#endif