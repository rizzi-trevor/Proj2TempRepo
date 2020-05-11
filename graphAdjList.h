#ifndef GRAPHADJLIST_H
#define GRAPHADJLIST_H

#include <iostream>         /// output/input stream
#include <string>           /// string class
#include <vector>           /// vector data structor
#include <algorithm>        /// algorithm
using namespace std;        /// standard library

/**
 *@author Kenneth Casimiro
 *@brief Adjacency graph list. Performs the trip using Dijkstra
 *@date November 2018
 */

struct adjListEdge	{               /// Edge
    string startCity;               /// Starting city.
    string endCity;                 /// Ending city.
    bool discEdge;                  /// Discovery Edge
    int weight;                     /// Distance between vertices

    adjListEdge() {                 /// Edge default constructor
        startCity = "";
        endCity   = "";
        discEdge  = false;
        weight    = 0;
    }
};

struct adjListVertex {              /// Vertex node of the graph

    string cityName;                /// Name of the city in the vertex.
    bool visited;                   /// Whether or not the vertex has already been visited.
    vector<adjListEdge> edgeList; 	/// List of incident edges.

    adjListVertex() {				/// Vertex default constructor
        cityName = "";              /// City name of vertex
        visited = false;            /// visited is false
    }
};

class graphAdjList {
public:
    /**
     *@authors Kenneth Casimiro
     * @brief graphAdjList()
     * Default constructor
     */
    graphAdjList();				/// default constructor

    /**
     *@authors Kenneth Casimiro
     * @brief ~graphAdjList()
     * Destructor
     */
    ~graphAdjList();			/// destructor

    /**
     *@authors Kenneth Casimiro
     * @brief empty()
     * Checks if the adj list is empty
     * @return bool
     */
    bool empty();				/// check if adj list is empty

    /**
     *@authors Kenneth Casimiro
     * @brief size()
     * Checks the size of the adj list
     * @return int
     */
    int size();					/// check the size of the adj list

    /**
     *@authors Kenneth Casimiro
     * @brief insertVertex(string cityName)
     * Inserts the vertex (stadium)
     * @param string cityName
     */
    void insertVertex(string cityName);								/// insert vertex

    /**
     *@authors Kenneth Casimiro
     * @brief findVertex(string cityName)
     * Finds a specific vertex (stadium)
     * @param string cityName
     * @return int
     */
    int findVertex(string cityName);						/// find the vertex

    /**
     *@authors Kenneth Casimiro
     * @brief insertEdge(string startCity, string endCity, int weight);
     * Inserts the edge for a vertex
     * @param string startCity, string endCity, int weight
     */
    void insertEdge(string startCity, string endCity, int weight);	/// insert edge to the vertex

    /**
     *@authors Kenneth Casimiro
     * @brief vertices()
     * Vector of the vertices
     * @return vector<string>
     */
    vector<string> vertices();										/// vertices vector

    /**
     *@authors Kenneth Casimiro
     * @brief edges()
     * Vector of the vertice edges
     * @return vector<string>
     */
    vector<string> edges();											/// edge vector

    /**
     *@authors Kenneth Casimiro
     * @brief shortestPathsDijkstra(string startingCity, vector<string> &insertGraph, int costs[], int parent[])
     * Finds the shortest distance for Dijkstras
     * @param string startingCity, vector<string> &insertGraph, int costs[], int parent[]
     */
    void shortestPathsDijkstra(string startingCity, 				/// Dijkstra algorithm
                               vector<string> &insertGraph,
                               int costs[], int parent[]);

    /**
     *@authors Kenneth Casimiro
     * @brief  returnPath(string startCity, string endCity, int parent[]);
     * Returns the path for A to B (start city to end city)
     * @param string startCity, string endCity, int parent[]
     * @return vector<string>
     */
    vector<string> returnPath(string startCity,
                              string endCity,
                              int parent[]);						/// Returns the edges

    /**
     *@authors Kenneth Casimiro
     * @brief  primJarnikMST(string startingCity, vector<string> &MST)
     * Returns the path for A to B (start city to end city)
     * @param string startCity, string endCity, int parent[]
     */
    int primJarnikMST(string startingCity, vector<string> &MST);	/// Prim-Jarnik

private:
    /**
     *@authors Kenneth Casimiro
     * @brief   findClosest(vector<string> &graph, int costs[], int parent[])
     * Finds the closest edge for the vertex
     * @param vector<string> &graph, int costs[], int parent[]
     */
    void findClosest(vector<string> &graph, int costs[], int parent[]);		/// find closest vertex

    /**
     *@authors Kenneth Casimiro
     * @brief distanceFromStart(string city, int costs[], int parent[])
     * Finds the distance from the start
     * @param string city, int costs[], int parent[]
     * @return int
     */
    int distanceFromStart(string city, int costs[], int parent[]);			/// find total distance in path

    /**
     *@authors Kenneth Casimiro
     * @brief smallestEdgeMST(vector<string> &MST)
     * Does the MST of the adj list
     * @param vector<string> &MST
     * @return int
     */
    int smallestEdgeMST(vector<string> &MST);								/// smallest edge for MST

    /**
     *@authors Kenneth Casimiro
     * @brief smallestEdge(int vertex)
     * Finds the smallest edge (Dijkstra)
     * @param int vertex
     * @return int
     */
    int smallestEdge(int vertex);											/// smallest edge finder

    /**
     *@authors Kenneth Casimiro
     * @brief distanceBetween(int city1, int city2)
     * Finds the distance between 2 nodes
     * @param int city1, int city2
     * @return int
     */
    int distanceBetween(int city1, int city2);								/// weight between vertices


    int verticesVisited();													/// all vertices visited
    int edgesDiscovered(int currentVertex);									/// number of edges discovered

    vector<adjListVertex> graph; 											/// Vector for adj list graph
    int MSTDistance; 														/// MST total distance
};


#endif // GRAPHADJLIST_H
