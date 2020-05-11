#include "graph.h"

void graph::addCity(string cityName) {
    cities.push_back(cityName);
    for(size_t i = 0; i < matrix.size(); i++) {
        matrix[i].push_back(0);
    }

    vector<int> temp;

    for(size_t i = 0; i < cities.size(); i++) {
        temp.push_back(0);
    }
    matrix.push_back(temp);
}

/// displays all in the matrix (including non edges)
void graph::displayAllMatrix() {
    for(size_t i = 0; i < matrix.size(); i++) {
        for(size_t j = 0; j < matrix[i].size(); j++) {
            cout << cities[i] << " to " << cities[j] << " is " << matrix[i][j] << endl;
        }
    }
}

/// adds the edge to the city node
void graph::addEdges(string startCity, string endCity, int weight) {
    int city1 = findCity(startCity);
    int city2 = findCity(endCity);

    if(city1 == -1 || city2 == -1) {
        cerr << "ERROR IN BFS - invalid city names; edge could not be added" << endl;
    } else {
        matrix[size_t(city1)][size_t(city2)] = weight;
        matrix[size_t(city2)][size_t(city1)] = weight;
    }
}

/// returns the matrix number for the city node
int graph::findCity(string searchCity) {
    size_t temp = size_t(-1);
    for(size_t i = 0; i < cities.size(); i++) {
        if(searchCity == cities[i]) {
            temp = i;
        }
    }
    if(temp == size_t(-1)) {
        cerr << "ERROR IN BFS - " << searchCity << " could not be found" << endl;
    }
    return int(temp);
}

/// displays all the matrix without non vertices
void graph::displayMatrix() {
    for(size_t i = 0; i < matrix.size(); i++) {
        cout << "ADDINGD EDGES - " << cities[i] << endl;
        cout << "*******************************************" << endl;
        for(size_t j = 0; j < matrix[i].size(); j++) {
            if(matrix[i][j] != 0) {
                cout << cities[i] << " to " << cities[j] << " is " << matrix[i][j] << endl;
            }
        }
        cout << endl;
    }
}

/// displays all the cities in the vector
void graph::displayCities() {
    cout << "CITIES ADDED" << endl;
    cout << "*******************************************" << endl;
    for(size_t i = 0; i < cities.size(); i++) {
        cout << cities[i] << endl;
    }
    cout << endl;
}

/// gets the edge length
int graph::getEdgeLength(string startCity, string endCity) {
    int city1 = findCity(startCity);
    int city2 = findCity(endCity);

    if(city1 == -1 || city2 == -1) {
        cerr << "ERROR IN BFS - invalid city names; edge could not be found" << endl;
        return 0;
    } else {
        return matrix[size_t(city1)][size_t(city2)];
    }
}

/// returns the column of weights
vector<int> graph::getAllEdges(int ofCity) {
    return matrix[size_t(ofCity)];
}

string graph::getCityName(int cityIndex) {
    return cities[size_t(cityIndex)];
}
