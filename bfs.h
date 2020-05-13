#ifndef BFS_H
#define BFS_H

#include "graph.h"



/**
 * @file
 */



/**
 * @brief The edge struct
 */
struct edge
{
    int city1;
    int city2;
    int weight;

    bool operator < (const edge &f) const{return weight < f.weight;};
};


/**
 * \class bfs
 *
 * \brief  class uses a graph structure to perform a Breadth First Search
 *
 * bfs uses an adjacency list structure as a graph. It provides the functionality
 * to perform a Breadth First Search (BFS) from a given starting city in the graph
 *
 */
class bfs {
public:
    /**
    * @brief Constructor
    * @param graph - graph strcture for use in the bfs
    * @return - none
    */
    bfs(graph iGraph);

    /**
    * @brief Initiates a search from the given (int) starting city
    * @param city - index of the city
    * @return - none
    */
    int startSearch(int city);

    /**
     * @brief startSearch
     * @param cityName
     * @return
     */
    int startSearch(string cityName);

    /**
     * @brief searchLevel
     */
    void searchLevel();

    /**
     * @brief sortEdges
     * @param toSort
     * @return
     */
    vector<edge> sortEdges(vector<edge> toSort);

    /**
     * @brief reinitialize
     * @param adjMatrix
     */
    void reinitialize(graph adjMatrix);

    /**
     * @brief getEdgesForThisLevel
     * @param citiesOnThisLevel
     * @return
     */
    vector<edge> getEdgesForThisLevel(vector<int> citiesOnThisLevel);

    /**
     * @brief getEdgesForCity
     * @param City
     * @return
     */
    vector<edge> getEdgesForCity(int City);

    /**
     * @brief edgeIsRepeat
     * @param edgeToCheck
     * @return
     */
    bool edgeIsRepeat(edge edgeToCheck);

    /**
     * @brief edgeIsCross
     * @param edgeToCheck
     * @return
     */
    bool edgeIsCross(edge edgeToCheck);

    /**
     * @brief printResults
     */
    void printResults();

    /**
     * @brief calcTotalDist
     * @return
     */
    int calcTotalDist();

private:

    vector<int> citiesThisLevel;
    vector<edge>edgesThisLevel;
    vector<int> nextLevel;
    vector<int> foundVerticies;
    vector<edge> discEdges;
    vector<edge> crossEdges;
    graph myGraph;
};


#endif // BFS_H
