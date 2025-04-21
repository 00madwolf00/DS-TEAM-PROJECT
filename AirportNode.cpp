/*
* AirportNode.cpp
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/20/2025
*/

#include "AirportNode.h"
#include "Edge.h"


AirportNode::~AirportNode(){
    for(Edge* edge : outgoingEdges){
        delete edge;
    }

    outgoingEdges.clear();
}
const vector<Edge*>& AirportNode::getEdges() const {
    return outgoingEdges;
}
