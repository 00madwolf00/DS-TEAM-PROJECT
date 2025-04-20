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
