/**
 * @file Statistics.hpp
 * @author MD (carpet02_steeps@icloud.com)
 * @brief This source code is part of cellular automaton simulator. 
 * @version 0.1
 * @date Created: 2019-12-08
 * 
 * @copyright Copyright (c) 2019 - 2023
 * 
 */

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>
#include <string>

using namespace std;

class Statistics
{
private:
    /* data */
    vector<double> Stats;
    vector<string> ColName;
    string Filedump;

    int Columns;
    int Records;
    int RecordsIncrement_cnt;

public:
    Statistics(int columns, string filename);
    ~Statistics();
    void SetColName(int column, string name);
    void AddData(int column, double data);
    void DumpToFile();
    void DumpToSTDOUT();
};


#endif