/**
 * @file render.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-02
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef RENDER_HPP
#define RENDER_HPP

#include "Grid.hpp"

void draw_rectangle(double X, double Y, double size);
void openGL_PrintGrid(Grid *grid);
void render_init(int argc, char* argv[]);

#endif