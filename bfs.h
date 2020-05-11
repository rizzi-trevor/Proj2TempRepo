#ifndef BFS_H
#define BFS_H

#include "graph.h"
struct edge {       ///used to store edges in the bfs
    int city1;
    int city2;
    int weight;

    bool operator < (const edge &f) const{return weight < f.weight;};
};



class bfs {
public:
    bfs(graph iGraph);
    int startSearch(int city);
    int startSearch(string cityName);
    void searchLevel();
    vector<edge> sortEdges(vector<edge> toSort);
    void reinitialize(graph adjMatrix);
    vector<edge> getEdgesForThisLevel(vector<int> citiesOnThisLevel);
    vector<edge> getEdgesForCity(int City);
    bool edgeIsRepeat(edge edgeToCheck);
    bool edgeIsCross(edge edgeToCheck);
    void printResults();
    int calcTotalDist();   ///runs at end after all discovery edges are found

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
