/**
 * @file Coordinates.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-01
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef COORDINATES_HPP
#define COORDINATES_HPP

class Coordinates
{
private:
    /* data */
    int X;
    int Y;
public:
    Coordinates(int x, int y);
    ~Coordinates();
    int GetX();
    int GetY();
};
#endif