/*
* AirportNode.h
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/19/2025
*/

#ifndef AIRPORTNODE_H
#define AIRPORTNODE_H

#include <string>
using namespace std;

class AirportNode {
private:
    string code;
    string city;
    string state;
    
public:
    AirportNode() {}

    AirportNode(const string& code, const string& city, const string& state) : code(code), city(city), state(state) {}
    
    const string& getCode() const{ 
        return code; 
    }

    const string& getCity() const{ 
        return city; 
    }

    const string& getState() const{ 
        return state; 
    }
    
    bool operator==(const AirportNode& other) const{
        return code == other.code;
    }
};

#endif
