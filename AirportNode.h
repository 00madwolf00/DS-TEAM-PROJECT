#ifndef AIRPORTNODE_H
#define AIRPORTNODE_H

#include <iostream>
#include <vector>

using namespace std;

class Edge;

class AirportNode{
private:
    string code;
    string city;
    string state;
    bool visited;
    vector<Edge*> outgoingEdges;

public:
    AirportNode(string& code, string& city = "", string& state = "");
    
    ~AirportNode();
    
    // Getters
    string getCode(){
        return code;
    }

    string getCity{
        return city;
    }

    string getState{
        return state;
    }

    bool isVisited(){
        return visited;
    }
    
    // Setters
    void setVisited(bool v){
        visited = v;
    }

    // Edge
    void addEdge(AirportNode* dest, double dist, double cost);
    vector<Edge*>& getEdges(){
        return outgoingEdges;
    }

    bool operator==(const AirportNode& other){
        return code == other.code;
    }
};

#endif //AIRPORT_H
