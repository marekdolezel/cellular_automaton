/**
 * @file Statistics.cpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-08
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Statistics.hpp"

Statistics::Statistics(int columns, string outputFilename)
{
    Columns = columns;
    Records = 0;
    Filedump = outputFilename;
    RecordsIncrement_cnt = 0;
    ColName = vector<string>(columns);

}

Statistics::~Statistics()
{
}

void Statistics::SetColName(int column, string name)
{
    ColName.at(column) = name;

}
void Statistics::AddData(int column, double data)
{
    if (column >= Columns) return; // Invalid column
    RecordsIncrement_cnt++;

    if (RecordsIncrement_cnt == Columns) {
        Records++;
        RecordsIncrement_cnt = 0;
    }

    Stats.push_back(data);
}

void Statistics::DumpToFile()
{
    ofstream filedump;

 
    // if (Filedump.empty()) {
    //     std::cout << "Statistics::DumpToFile: no file has been specified, dump aborted." << std::endl;
    //     return;
    // }

    // return;

    filedump.open(Filedump);

    if (!filedump.is_open()) {
        std::cerr << "Error opening file: " << Filedump << std::endl;
        std::cerr << "Results were not dumped to csv file" << std::endl;
        return;
    }


    for (int column = 0; column < Columns; column++) {
        if (column + 1 == Columns) 
            filedump << ColName.at(column);
        else
            filedump << ColName.at(column) << ",";
    }
    filedump << endl;

    for (int record = 0; record < Records; record++) {
        for (int column = 0; column < Columns; column++) {
            if (column + 1 == Columns) 
                filedump << Stats.at(Columns*record + column);
            else
                filedump << Stats.at(Columns*record + column) << ",";
        }
        filedump << endl;
    }

    filedump.close();
}

void Statistics::DumpToSTDOUT()
{

}
