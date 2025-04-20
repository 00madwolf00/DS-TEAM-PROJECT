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
        string fields[6];
        for (int i = 0; i < 6 && getline(ss, fields[i], ','); ++i) {
            // Handle quoted field that contains commas
            if (!fields[i].empty() && fields[i][0] == '"' && fields[i].back() != '"') {
                string continuation;
                while (getline(ss, continuation, ',')) {
                    fields[i] += "," + continuation;
                    if (!continuation.empty() && continuation.back() == '"') break;
                }
            }

            // Strip surrounding quotes if present
            if (!fields[i].empty() && fields[i].front() == '"') fields[i] = fields[i].substr(1);
            if (!fields[i].empty() && fields[i].back() == '"') fields[i].pop_back();
        }

        string origin      = fields[0];
        string destination = fields[1];
        string originCity  = fields[2];
        string destCity    = fields[3];
        string distStr     = fields[4];
        string costStr     = fields[5];

        int distance = 0;
        int cost = 0;

        try {
            distance = stoi(distStr);
            cost = stoi(costStr);
        } catch (const exception& e) {
            cerr << "Error reading line " << lineCount << ": " << e.what() << endl;
            cerr << "  distance: '" << distStr << "', cost: '" << costStr << "'" << endl;
            cerr << "  Error: " << e.what() << endl;
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