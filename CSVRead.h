/*
* CSVRead.h
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/19/2025
*/

#ifndef CSVREAD_H
#define CSVREAD_H

#include "Graph.h"
#include <string>

using namespace std;

class CSVReader{
public:
    static bool loadAirportsCSV(const string& filename, AirportGraph& graph);
};

#endif
