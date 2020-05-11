#include "dfsgraph.h"

dfsGraph::dfsGraph()
{
    dfsDistance = 0;
}

dfsGraph::~dfsGraph()
{

}

bool dfsGraph::empty()
{
    return graph.empty();
}

int dfsGraph::size()
{
    return graph.size();
}

unsigned int dfsGraph::findVertex(string city)
{
    unsigned int index = 0;
    bool found = false;

    while(index < graph.size() && !found)
    {
        if(graph.at(index).city == city)
        {
            found = true;
        }
        else
        {
            index++;
        }
    }

    return index;
}

void dfsGraph::insertVertex(string city)
{

    if(findVertex(city) == graph.size())
    {
        Vertex newVertex;

        newVertex.city = city;
        newVertex.visited = false;

        cout <<"CITY: "<< newVertex.city << " - HAS BEEN ADDED."<< endl;

        graph.push_back(newVertex);
    }
}

void dfsGraph::insertEdge(string u, string v, int weight)
{
    /// Returns the index of the vertex.
    unsigned int index = findVertex(u);

    /// Adds the vertex to the dfsGraph if it does not yet exist and performs a
    /// recursive call, else adds the edge to the edgeList of the specified vertex.
    if(index == graph.size())
    {
        insertVertex(u);

        insertEdge(u, v, weight);
    }
    else
    {
        Edge newEdge;

        newEdge.u = u;
        newEdge.v = v;
        newEdge.weight = weight;

        graph.at(index).edgeList.push_back(newEdge);
    }
}

vector<string> dfsGraph::vertices()
{
    vector<string> cityNames; /// Vector of city names.

    for(unsigned int i = 0; i < graph.size(); i++)
    {
        cityNames.push_back(graph[i].city);
    }

    return cityNames;
}

vector<string> dfsGraph::edges()
{
    vector<string> edgeList; /// Vector of edges.

    /// Adds the edges in the dfsGraph to the vector if the node has edges.
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        if(graph.at(i).edgeList.size() != 0)
        {
            /// Pushes the edge pair onto the vector in (u, v) format.
            for(unsigned int j = 0; j < graph.at(i).edgeList.size(); j++)
            {
                edgeList.push_back("(" + graph.at(i).edgeList.at(j).u + ", "
                                       + graph.at(i).edgeList.at(j).v + ")");
            }
        }
    }

    return edgeList;
}

int dfsGraph::DFS(string startingCity, vector<string> &dfs)
{
    /// Gets the dfsGraph index of the vertex being visited.
    int currVertex = findVertex(startingCity);

    /// Visits the vertex.
    graph.at(currVertex).visited = true;

    /// Searches the vector of visited vertices for the city being visited.
    vector<string>::iterator nextCityIt = find(dfs.begin(), dfs.end(), startingCity);

    /// Adds the vertex to the vector if it is not already in the vector.
    if(nextCityIt == dfs.end())
    {
        dfs.push_back(startingCity);
    }

    /// Performs a recursive call on itself to visit all vertices in the dfsGraph.
    if(verticesVisited() != graph.size())
    {
        /// Gets the dfsGraph index of the next closest city in the dfsGraph.
        int nextVertex = smallestEdgeDFS(currVertex, dfs);

        /// Performs recursive call to visit the next closest city.
        DFS(graph.at(nextVertex).city, dfs);
    }

    return dfsDistance;
}

vector<string> dfsGraph::getDiscoveryEdges(vector<string> &dfs)
{
    vector<Edge> discEdges; /// Vector of the discovery edges.

    /// Adds the discovery edges to the vector in the order they were discovered.
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        int dfsIndex = findVertex(dfs.at(i));

        for(unsigned int j = 0; j < graph.at(dfsIndex).edgeList.size(); j++)
        {
            /// Only adds the edge to the vector if it is a discovery edge.
            if(graph.at(dfsIndex).edgeList.at(j).discoveryEdge)
            {
                discEdges.push_back(graph.at(dfsIndex).edgeList.at(j));
            }
        }
    }

    /// Deletes edges with the same vertices to avoid duplicates.
    deleteDuplicates(discEdges);

    /// Iterator to the beginning of the vector of discovery edges.
    vector<Edge>::iterator edgeIt = discEdges.begin();

    vector<string> discoveryEdges; /// Vector of discovery edge pairs.

    /// Adds the discovery edges to the string vector in (u, v) format.
    while(edgeIt != discEdges.end())
    {
        discoveryEdges.push_back("(" + edgeIt->u + ", " + edgeIt->v + ")");

        edgeIt++;
    }

    return discoveryEdges;
}

vector<string> dfsGraph::getBackEdges(vector<string> &dfs)
{
    vector<Edge> backEdges; /// Vector of back edges.

    /// Adds the back edges to the vector in the order they were discovered.
    for(unsigned int i = 0; i < graph.size(); i++)
    {
        int dfsIndex = findVertex(dfs.at(i));

        for(unsigned int j = 0; j < graph.at(dfsIndex).edgeList.size(); j++)
        {
            /// Only adds the edge to the vector if it is a back edge.
            if(!(graph.at(dfsIndex).edgeList.at(j).discoveryEdge))
            {
                backEdges.push_back(graph.at(dfsIndex).edgeList.at(j));
            }
        }
    }

    /// Deletes edges with the same vertices to avoid duplicates.
    deleteDuplicates(backEdges);

    /// Iterator to the beginning of the vector of back edges.
    vector<Edge>::iterator edgeIt = backEdges.begin();

    vector<string> backEdgeList; // Vector of back edge pairs.

    /// Adds the back edges to the string vector in (u, v) format.
    while(edgeIt != backEdges.end())
    {
        backEdgeList.push_back("(" + edgeIt->u + ", " + edgeIt->v + ")");

        edgeIt++;
    }

    return backEdgeList;
}

int dfsGraph::smallestEdgeDFS(int currVertex, vector<string> &dfs)
{
    /// Searches for the next closest edge if all edges of the current vertex
    /// haven't been visited yet, else backtracks to find a vertex whose edges
    /// haven't all been discovered.
    if(edgesDiscovered(currVertex) != graph.at(currVertex).edgeList.size())
    {
        /// Edge list vertex of the closest city.
        int smallestIndex = 0;

        /// Edge list vertex of the city whose distance is being compared to the
        /// city at edgeList.at(smallestIndex).
        int compIndex = smallestIndex + 1;

        /// Gets the size of the edgeList for the current vertex.
        int size = graph.at(currVertex).edgeList.size();

        /// Finds the next closest city that has not been visited yet.
        while(compIndex < size)
        {
            /// Gets the dfsGraph index of the next closest city.
            int smallestVertex = findVertex(graph.at(currVertex).edgeList.at(smallestIndex).v);

            /// Gets the dfsGraph index of the city in the edge list being comapred
            /// to the city at edgeList.at(smallestIndex).
            int compVertex = findVertex(graph.at(currVertex).edgeList.at(compIndex).v);


            if(graph.at(smallestVertex).visited)
            {
                smallestIndex++;
            }
            else
            {

                if(!(graph.at(compVertex).visited))
                {
                    if(graph.at(currVertex).edgeList.at(smallestIndex).weight >=
                       graph.at(currVertex).edgeList.at(compIndex).weight)
                    {
                        smallestIndex = compIndex;
                    }
                }
            }

            /// Increments compIndex so that it is always the after smallestIndex.
            compIndex++;
        }

        /// Marks the edge that has the smallest weight as a discovery edge.
        graph.at(currVertex).edgeList.at(smallestIndex).discoveryEdge = true;



        /// Adds the distance to the overall distance traveled.
        dfsDistance += graph.at(currVertex).edgeList.at(smallestIndex).weight;

        /// Gets the name of the city that is the closest to the current city.
        string nextCity = graph.at(currVertex).edgeList.at(smallestIndex).v;

        /// Finds the dfsGraph index of the closest city.
        smallestIndex = findVertex(nextCity);

        for(unsigned int i = 0; i < graph.at(smallestIndex).edgeList.size(); i++)
        {
            if(graph.at(currVertex).city == graph.at(smallestIndex).edgeList.at(i).v)
            {
                graph.at(smallestIndex).edgeList.at(i).discoveryEdge = true;
            }
        }

        return smallestIndex;
    }
    else
    {
        /// Iterator that gets the location of the current city in the vector of
        /// names that contains the cities in the order they were visited.
        vector<string>::iterator dfsIt = find(dfs.begin(), dfs.end(),
                                              graph.at(currVertex).city);

        /// Decrements the iterator to the previous city visited.
        dfsIt--;

        /// Finds the dfsGraph index of the previous city visited.
        int backIndex = findVertex(*dfsIt);

        /// Preforms a recursive call to check if the previous city visited has
        /// any unvisited edges to continue the DFS.
        return smallestEdgeDFS(backIndex, dfs);
    }
}

int dfsGraph::distance(Vertex * v1, Vertex * v2)
{
    /// find connecting edge
    for (unsigned int i=0; i<v1->edgeList.size(); i++) {
        if (v1->edgeList.at(i).u == v2->city || v1->edgeList.at(i).v == v2->city)
            return v1->edgeList.at(i).weight;
    }
    return -1;
}

string dfsGraph::otherVertex(Edge currEdge, string startingCity)
{
    if(currEdge.u == startingCity)
        return currEdge.v;
    else
        return currEdge.u;
}

unsigned int dfsGraph::verticesVisited()
{
    int numVisited = 0; /// Number of vertices visited.

    /// Iterator to the first vertex in the dfsGraph.
    vector<Vertex>::iterator dfsGraphIt = graph.begin();

    /// Counts the number of vertices in the dfsGraph that are marked as visited.
    while(dfsGraphIt != graph.end())
    {
        if(dfsGraphIt->visited)
        {
            numVisited++;
        }

        dfsGraphIt++;
    }

    return numVisited;
}

unsigned int dfsGraph::edgesDiscovered(int currVertex)
{
    int numVisited = 0; /// Number of edges discovered.

    /// Counts the number of edges at the current vertex that have been discovered.
    for(unsigned int i = 0; i < graph.at(currVertex).edgeList.size(); i++)
    {
        if(graph.at(findVertex(graph.at(currVertex).edgeList.at(i).v)).visited)
        {
            numVisited++;
        }
    }

    return numVisited;
}

void dfsGraph::deleteDuplicates(vector<Edge> &edgeList)
{
    vector<Edge>::iterator listIt = edgeList.begin();

    /// Traverses the list of edges to delete pairs that are the same.
    while(listIt != edgeList.end())
    {
        vector<Edge>::iterator compIt = listIt + 1;

        bool deleted = false;

        /// Deletes the first instance of an edge that has the same pair as
        /// the edge pointed to by listIt.
        while(compIt != edgeList.end() && !deleted)
        {
            if(listIt->u == compIt->v && listIt->v == compIt->u)
            {
                edgeList.erase(compIt);

                deleted = true;
            }
            else
            {
                compIt++;
            }
        }

        listIt++;
    }
}
