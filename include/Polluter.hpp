/**
 * @file Polluter.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-11-29
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef POLLUTER_HPP
#define POLLUTER_HPP


class Polluter
{
private:
    /* data */
    double Pollution;

    int X;
    int Y;
public:
    Polluter(int x, int y);
    Polluter(int x, int y, double pollution);
    ~Polluter();
    double GetPollutionAmount();
    void UpdatePollutionAmount(double newPollution);

    int getX();
    int getY();
};

#endif