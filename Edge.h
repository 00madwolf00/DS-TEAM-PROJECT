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