/*
* Edge.h
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

#ifndef EDGE_H
#define EDGE_H

#include "AirportNode.h"
using namespace std;

class Edge {
public:
    AirportNode* to;
    double distance;
    double cost;

    Edge(AirportNode*dest, double dist, double cost);
};

#endif //EDGE_H
