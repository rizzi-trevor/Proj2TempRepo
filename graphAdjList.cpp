#include "graphAdjList.h"


graphAdjList::graphAdjList()
{
    MSTDistance = 0;
}

graphAdjList::~graphAdjList()
{

}

bool graphAdjList::empty()
{
    return graph.empty();
}

int graphAdjList::size()
{
    return graph.size();
}

/// find vertex
int graphAdjList::findVertex(string city)
{
    int index = 0;
    bool found = false;

    /// Finds the city that you're looking for
    while(index < graph.size() && !found)
    {
        if(graph.at(index).cityName == city)
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

/// insert the vertex
void graphAdjList::insertVertex(string cityName)
{
    /// Adds the vertex to the graph if it does not yet exist.
    if(findVertex(cityName) == graph.size())
    {
        adjListVertex newVertex;

        newVertex.cityName = cityName;
        newVertex.visited = false;

        cout << newVertex.cityName << endl;

        graph.push_back(newVertex);
    }
}


void graphAdjList::insertEdge(string startCity, string endCity, int weight) {
    int index = findVertex(startCity);


    if(index == graph.size()) {
        insertVertex(startCity);

        insertEdge(startCity, endCity, weight);
    }
    else
    {
        adjListEdge newEdge;

        newEdge.startCity = startCity;
        newEdge.endCity = endCity;
        newEdge.weight = weight;

        graph.at(index).edgeList.push_back(newEdge);
    }
}



vector<string> graphAdjList::vertices()
{
    vector<string> cityNames;

    for(int i = 0; i < graph.size(); i++) {
        cityNames.push_back(graph[i].cityName);
    }

    return cityNames;
}



vector<string> graphAdjList::edges() {
    vector<string> edgeList;


    for(int i = 0; i < graph.size(); i++)
    {
        if(graph.at(i).edgeList.size() != 0)
        {
            for(int j = 0; j < graph.at(i).edgeList.size(); j++)
            {
                edgeList.push_back("(" + graph.at(i).edgeList.at(j).startCity + ", "
                                       + graph.at(i).edgeList.at(j).endCity + ")");
            }
        }
    }

    return edgeList;
}

int graphAdjList::verticesVisited()
{
    int visits = 0;

    vector<adjListVertex>::iterator graphIt = graph.begin();

    while(graphIt != graph.end())
    {
        if(graphIt->visited)
        {
            visits++;
        }
        graphIt++;
    }

    return visits;
}

int graphAdjList::edgesDiscovered(int currentVertex) {
    int visits = 0;


    for(int i = 0; i < graph.at(currentVertex).edgeList.size(); i++)
    {
        if(graph.at(findVertex(graph.at(currentVertex).edgeList.at(i).endCity)).visited)
        {
            visits++;
        }
    }

    return visits;
}


void graphAdjList::shortestPathsDijkstra(string startingCity, vector<string> &insertGraph,
                                         int costs[], int parent[])
{
    if(verticesVisited() == graph.size())
    {
        for (int i=0; i < graph.size(); i++)
        {
            graph[i].visited = false;

            for (int j=0; j < graph.at(i).edgeList.size(); j++)
            {
                graph[i].edgeList[j].discEdge = false;
            }
        }
    }

    int currentVertex = findVertex(startingCity);

    insertGraph.push_back(graph[currentVertex].cityName);

    costs[currentVertex]  = 0;
    parent[currentVertex] = -1;

    graph[currentVertex].visited = true;

    while(insertGraph.size() != size()) {
        findClosest(insertGraph, costs, parent);
    }
}

vector<string> graphAdjList::returnPath(string startCity, string endCity, int parent[])
{
    vector<string> path;

    int vertex = findVertex(endCity);

    while(parent[vertex] != -1)
    {
        path.push_back(graph[vertex].cityName);
        vertex = parent[vertex];
    }

    path.push_back(graph[vertex].cityName);

    reverse(path.begin(), path.end());

    return path;
}

int graphAdjList::primJarnikMST(string startingCity, vector<string> &MST)
{
    if(verticesVisited() == size())
    {
        for (int i=0; i<graph.size(); i++)
        {
            graph[i].visited = false;

            for (int j=0; j< graph.at(i).edgeList.size(); j++)
            {
                graph[i].edgeList[j].discEdge = false;
            }
        }

        MSTDistance = 0;
    }

    int currVertex = findVertex(startingCity);

    graph.at(currVertex).visited = true;

    MST.push_back(startingCity);

    if(MST.size() != size())
    {
        int nextVertex = smallestEdgeMST(MST);
        primJarnikMST(graph.at(nextVertex).cityName, MST);
    }

    return MSTDistance;
}

/// finds the closest vertex
void graphAdjList::findClosest(vector<string> &T, int costs[], int parent[])
{
    if(T.size() == 1)
    {
        int frontVer = findVertex(T.front());

        int nextVer = smallestEdge(frontVer);

        costs[nextVer] = distanceBetween(frontVer, nextVer);
        parent[nextVer] = frontVer;

        graph[nextVer].visited = true;

        T.push_back(graph[nextVer].cityName);
    }
    else
    {
        int smallID = 0;
        int comparatorID = smallID + 1;

        int smallDistance;
        int comparatorDistance;

        int size = T.size();

        while(comparatorID < size)
        {
            int smallVer = findVertex(T[smallID]);
            int compVer = findVertex(T[comparatorID]);

            if(graph[smallVer].edgeList.size() == edgesDiscovered(smallVer))
            {
                smallID++;
            }
            else
            {
                if(graph[compVer].edgeList.size() != edgesDiscovered(compVer))
                {
                    smallDistance = distanceBetween(smallVer, smallestEdge(smallVer))
                                + distanceFromStart(graph[smallVer].cityName, costs,
                                                    parent);

                    comparatorDistance =  distanceBetween(compVer, smallestEdge(compVer))
                                + distanceFromStart(graph[compVer].cityName, costs,
                                                    parent);

                    if(smallDistance > comparatorDistance)
                    {
                        smallID = comparatorID;
                        smallDistance = comparatorDistance;
                    }
                }
            }
            comparatorID++;
        }

        int smallestVertex = smallestEdge(findVertex(T[smallID]));

        costs[smallestVertex] = smallDistance;
        parent[smallestVertex] = findVertex(T[smallID]);

        graph[smallestVertex].visited = true;

        T.push_back(graph[smallestVertex].cityName);
    }
}


int graphAdjList::distanceFromStart(string city, int costs[], int parent[])
{
    int distance = 0;

    int vertex = findVertex(city);

    while(costs[vertex] != 0)
    {
        distance += distanceBetween(vertex, parent[vertex]);
        vertex = parent[vertex];
    }

    return distance;
}

int graphAdjList::smallestEdgeMST(vector<string> &MST)
{
    if(MST.size() == 1) {
        int smallestVertex = smallestEdge(findVertex(MST.front()));

        MSTDistance += distanceBetween(findVertex(MST.front()), smallestVertex);

        cout << MST.front() << ", " << graph[smallestVertex].cityName
             << " (" << distanceBetween(findVertex(MST.front()), smallestVertex) << ")";
        cout << endl;

        return smallestEdge(findVertex(MST.front()));
    }
    else
    {
        int smallID = 0;
        int compId = smallID + 1;

        int size = MST.size();

        while(compId < size) {
            int smallVer = findVertex(MST[smallID]);
            int compVer = findVertex(MST[compId]);

            if(graph[smallVer].edgeList.size() == edgesDiscovered(smallVer))
            {
                smallID++;
            }
            else {
                if(graph[compVer].edgeList.size() != edgesDiscovered(compVer))
                {
                    int smallDist = distanceBetween(smallVer, smallestEdge(smallVer));
                    int compDist =  distanceBetween(compVer, smallestEdge(compVer));
                    if(smallDist > compDist)
                    {
                        smallID = compId;
                    }
                }
            }
            compId++;
        }

        MSTDistance += distanceBetween(findVertex(MST[smallID]),
                                       smallestEdge(findVertex(MST[smallID])));

        int smallestVertex = findVertex(MST[smallID]);

        string nextCity = graph.at(smallestEdge(smallestVertex)).cityName;

        cout << MST[smallID] << " to " << nextCity << " (" << distanceBetween(findVertex(MST[smallID]),
                   smallestEdge(findVertex(MST[smallID]))) << ")";
        cout << endl;

        smallID = findVertex(nextCity);

        return smallID;
    }
}

int graphAdjList::smallestEdge(int vertex)
{
    int smallestIndex = 0;

    int compIndex = smallestIndex + 1;

    int size = graph.at(vertex).edgeList.size();

    while(compIndex < size) {
        int smallestVertex = findVertex(graph.at(vertex).edgeList.at(smallestIndex).endCity);

        int compVertex = findVertex(graph.at(vertex).edgeList.at(compIndex).endCity);

        if(graph.at(smallestVertex).visited) {
            smallestIndex++;
        }
        else {
            if(!(graph.at(compVertex).visited)) {
                if(graph.at(vertex).edgeList.at(smallestIndex).weight >=
                        graph.at(vertex).edgeList.at(compIndex).weight) {
                    smallestIndex = compIndex;
                }
            }
        }
        compIndex++;
    }
    smallestIndex = findVertex(graph.at(vertex).edgeList.at(smallestIndex).endCity);

    return smallestIndex;
}

int graphAdjList::distanceBetween(int city1, int city2) {
    int i = 0;

    while(graph[city1].edgeList[i].endCity != graph[city2].cityName) {
        i++;
    }
    return graph[city1].edgeList[i].weight;
}
