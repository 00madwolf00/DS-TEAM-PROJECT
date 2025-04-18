#ifndef EDGE_H
#define EDGE_H

#include "AirportNode.h"
using namespace std;

class Edge {
public:
    int to;
    double distance;
    double cost;

    Edge(int destIndex, double dist, double cost);
};

#endif //EDGE_H