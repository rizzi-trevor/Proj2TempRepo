#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>			/// input/output stream
#include <string>			/// string
#include <vector>			/// vector
#include <algorithm>
#include <QDebug>
using namespace std;



/**
 * \class graph
 *
 * \brief  Graph data strcture for use in the BFS class
 *
 * Graph is an adjacency list
 *
 */

class graph {
public:

    void addCity(string cityName);                                  /// addCity to city vector

    void displayAllMatrix();										/// displays every edge in the matrix

    void addEdges(string startCity, string endCity, int weight);	/// add edges to a node

    int findCity(string searchCity);								/// finds the node city

    void displayMatrix();                                           /// display all known edges

    int getEdgeLength(string startCity, string endCity);			/// get edge length

    void displayCities();                                           /// displays all cities

    vector<int> getAllEdges(int ofCity);                            /// returns the column of weights

    string getCityName(int cityIndex);                              /// returns the name of the city

private:
    vector<vector<int> > matrix;
    vector<string> cities;
};

#endif // GRAPH_H
