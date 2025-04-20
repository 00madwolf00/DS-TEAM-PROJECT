/*
* CSVRead.cpp
* Names: Allicyan Chin, Jaheem Clayton, Jasmine Heymann
* Course: COP-3415
* Last Modified: 04/19/2025
*/

#include "CSVRead.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

bool CSVReader::loadAirportsCSV(const string& filename, Graph& graph) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }
    
    string line;
    getline(file, line); // skip header
    int lineCount = 0;

    while (getline(file, line)) {
        lineCount++;

        stringstream ss(line);
        string origin, destination, originCity, destCity, distStr, costStr;

        getline(ss, origin, ',');
        getline(ss, destination, ',');
        getline(ss, originCity, ',');
        getline(ss, destCity, ',');
        getline(ss, distStr, ',');
        getline(ss, costStr, ',');

        int distance = 0;
        int cost = 0;

        try {
            distance = stoi(distStr);
            cost = stoi(costStr);
        } catch (const exception& e) {
            cerr << "Error reading line " << lineCount << ": " << e.what() << endl;
            continue;
        }

        // Add airports and flights
        graph.addAirport(origin);
        graph.addAirport(destination);
        graph.addFlight(origin, destination, distance, cost);
    }

    file.close();
    cout << "Loaded " << lineCount << " flights from " << filename << endl;
    return true;
}