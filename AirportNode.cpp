#include "AirportNode.h"
#include "Edge.h"


AirportNode::~AirportNode(){
    for(Edge* edge : outgoingEdges){
        delete edge;
    }

    outgoingEdges.clear();
}


