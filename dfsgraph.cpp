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
    unsigned int index = findVertex(u);

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
    vector<string> cityNames;

    for(unsigned int i = 0; i < graph.size(); i++)
    {
        cityNames.push_back(graph[i].city);
    }

    return cityNames;
}

vector<string> dfsGraph::edges()
{
    vector<string> edgeList;


    for(unsigned int i = 0; i < graph.size(); i++)
    {
        if(graph.at(i).edgeList.size() != 0)
        {

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
    int currVertex = findVertex(startingCity);

    graph.at(currVertex).visited = true;

    vector<string>::iterator nextCityIt = find(dfs.begin(), dfs.end(), startingCity);

    if(nextCityIt == dfs.end())
    {
        dfs.push_back(startingCity);
    }

    if(verticesVisited() != graph.size())
    {
        int nextVertex = smallestEdgeDFS(currVertex, dfs);

        DFS(graph.at(nextVertex).city, dfs);
    }

    return dfsDistance;
}

vector<string> dfsGraph::getDiscoveryEdges(vector<string> &dfs)
{
    vector<Edge> discEdges;

    for(unsigned int i = 0; i < graph.size(); i++)
    {
        int dfsIndex = findVertex(dfs.at(i));

        for(unsigned int j = 0; j < graph.at(dfsIndex).edgeList.size(); j++)
        {
            if(graph.at(dfsIndex).edgeList.at(j).discoveryEdge)
            {
                discEdges.push_back(graph.at(dfsIndex).edgeList.at(j));
            }
        }
    }

    deleteDuplicates(discEdges);

    vector<Edge>::iterator edgeIt = discEdges.begin();

    vector<string> discoveryEdges;

    while(edgeIt != discEdges.end())
    {
        discoveryEdges.push_back("(" + edgeIt->u + ", " + edgeIt->v + ")");

        edgeIt++;
    }

    return discoveryEdges;
}

vector<string> dfsGraph::getBackEdges(vector<string> &dfs)
{
    vector<Edge> backEdges;

    for(unsigned int i = 0; i < graph.size(); i++)
    {
        int dfsIndex = findVertex(dfs.at(i));

        for(unsigned int j = 0; j < graph.at(dfsIndex).edgeList.size(); j++)
        {
            if(!(graph.at(dfsIndex).edgeList.at(j).discoveryEdge))
            {
                backEdges.push_back(graph.at(dfsIndex).edgeList.at(j));
            }
        }
    }

    deleteDuplicates(backEdges);

    vector<Edge>::iterator edgeIt = backEdges.begin();

    vector<string> backEdgeList;

    while(edgeIt != backEdges.end())
    {
        backEdgeList.push_back("(" + edgeIt->u + ", " + edgeIt->v + ")");

        edgeIt++;
    }

    return backEdgeList;
}

int dfsGraph::smallestEdgeDFS(int currVertex, vector<string> &dfs)
{

    if(edgesDiscovered(currVertex) != graph.at(currVertex).edgeList.size())
    {
        int smallestIndex = 0;

        int compIndex = smallestIndex + 1;

        int size = graph.at(currVertex).edgeList.size();

        while(compIndex < size)
        {
            int smallestVertex = findVertex(graph.at(currVertex).edgeList.at(smallestIndex).v);

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

            compIndex++;
        }

        graph.at(currVertex).edgeList.at(smallestIndex).discoveryEdge = true;



        dfsDistance += graph.at(currVertex).edgeList.at(smallestIndex).weight;

        string nextCity = graph.at(currVertex).edgeList.at(smallestIndex).v;

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
        vector<string>::iterator dfsIt = find(dfs.begin(), dfs.end(),
                                              graph.at(currVertex).city);

        dfsIt--;

        int backIndex = findVertex(*dfsIt);

        return smallestEdgeDFS(backIndex, dfs);
    }
}

int dfsGraph::distance(Vertex * v1, Vertex * v2)
{
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
    int numVisited = 0;

    vector<Vertex>::iterator dfsGraphIt = graph.begin();

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
    int numVisited = 0;

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

    while(listIt != edgeList.end())
    {
        vector<Edge>::iterator compIt = listIt + 1;

        bool deleted = false;

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
