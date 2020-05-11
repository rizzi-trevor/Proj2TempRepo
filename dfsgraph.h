#ifndef DFSGRAPH_H
#define DFSGRAPH_H

#include <QDialog>       ///  base class of dialog windows
#include <QListWidget>   /// provides an item-based list widget

#include <iostream>      /// Used to create/manipulate output (C++)
#include <fstream>       /// Used to read from file, write to file
#include <string>        /// Used for passing through arguments (as opposed to QString)
#include <vector>        /// Used to store data
#include <algorithm>     /// Used for DFS processes
using namespace std;


struct Edge
{
    string u; /// Starting city.
    string v; /// Ending city.
    bool discoveryEdge; /// Whether or not edge is a discovery edge.
    int weight; /// Distance between the cities.

    /// Edge object constructor.
    Edge()
    {
        u = "";
        v = "";
        discoveryEdge = false;
        weight = 0;
    }
};

/// Struct representing a vertex in the dfsGraph.
struct Vertex
{
    string city; /// Name of the city in the vertex.
    bool visited; /// Whether or not the vertex has already been visited.
    vector<Edge> edgeList; /// List of incident edges.

    /// Vertex object constructor.
    Vertex()
    {
        city = "";
        visited = false;
    }
};

/// dfsGraph class that uses an adjacency list to store edges.
class dfsGraph
{
public:
    dfsGraph();
    ~dfsGraph();

    bool empty();


    int size();

    void insertVertex(string city);


    unsigned int findVertex(string city);


    void insertEdge(string u, string v, int weight);


    vector<string> vertices();


    vector<string> edges();


    int DFS(string startingCity, vector<string> &dfs);


    vector<string> getDiscoveryEdges(vector<string> &dfs);


    vector<string> getBackEdges(vector<string> &dfs);

private:

    int smallestEdgeDFS(int currVertex, vector<string> &dfs);


    unsigned int verticesVisited();


    unsigned int edgesDiscovered(int currVertex);


    void deleteDuplicates(vector<Edge> &edgeList);

    vector<Vertex> graph; /// Vector of vertices used to represent a dfsGraph.

    int dfsDistance; /// Distance traveled during DFS.

    string otherVertex(Edge currEdge, string startingCity);

    int distance(Vertex * v1, Vertex * v2);
};
#endif // DFSGRAPH_H
