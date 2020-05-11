#include "bfs.h"

bfs::bfs(graph iGraph){
    myGraph = iGraph;
}

void bfs::reinitialize(graph adjMatrix) {
    myGraph = adjMatrix;
}

int bfs::startSearch(string cityName) {
    return startSearch(myGraph.findCity(cityName));
}

int bfs::startSearch(int city) {
    citiesThisLevel.push_back(city);
    foundVerticies.push_back(city);

    searchLevel();
    printResults();
    return calcTotalDist();
}

void bfs::searchLevel() {
    vector<edge>edgeList = getEdgesForThisLevel(citiesThisLevel);
    edgeList = sortEdges(edgeList);

    for(size_t index = 0; index < edgeList.size(); index++){
        if(edgeIsRepeat(edgeList[index])){
            //repeated edge, do nothing
        }else if(edgeIsCross(edgeList[index])) {
            crossEdges.push_back(edgeList[index]);
        }else{
            discEdges.push_back(edgeList[index]);
            foundVerticies.push_back(edgeList[index].city2);
            nextLevel.push_back(edgeList[index].city2);
        }
    }

    citiesThisLevel = nextLevel;
    nextLevel.clear();
    if(citiesThisLevel.size() != 0)
    {
        searchLevel();
    }
}

vector<edge> bfs::getEdgesForThisLevel(vector<int> citiesOnThisLevel) {
    vector<edge> retVal;
    vector<edge> toConcat;
    for(size_t index = 0; index < citiesOnThisLevel.size(); index++)
    {
        toConcat = getEdgesForCity(citiesOnThisLevel[index]);
        retVal.insert(retVal.end(), toConcat.begin(), toConcat.end());
    }

    return retVal;
}

vector<edge> bfs::getEdgesForCity(int City) {
    vector<edge> retVal;
    edge toAdd;

    vector<int> weights = myGraph.getAllEdges(City);
    for(size_t index = 0; index < weights.size(); index++) {
        if(weights[index] != 0){
            toAdd.city1 = City;
            toAdd.city2 = int(index);
            toAdd.weight = weights[index];
            retVal.push_back(toAdd);
        }
    }

    return retVal;
}


vector<edge> bfs::sortEdges(vector<edge> toSort) {
    vector<edge> temp = toSort;

    std::sort(temp.begin(), temp.end());

    return temp;
}

bool bfs::edgeIsRepeat(edge edgeToCheck) {
    for(size_t index = 0; index < discEdges.size(); index++)
    {
        if((edgeToCheck.city1 == discEdges[index].city1 && edgeToCheck.city2 == discEdges[index].city2)
                ||(edgeToCheck.city1 == discEdges[index].city2 && edgeToCheck.city2 == discEdges[index].city1)){
            return true;
        }
    }
    for(size_t index = 0; index < crossEdges.size(); index++)
    {
        if((edgeToCheck.city1 == crossEdges[index].city1 && edgeToCheck.city2 == crossEdges[index].city2)
                ||(edgeToCheck.city1 == crossEdges[index].city2 && edgeToCheck.city2 == crossEdges[index].city1)){
            return true;
        }
    }
    //else
    return false;
}

bool bfs::edgeIsCross(edge edgeToCheck) {
    for(size_t index = 0; index < foundVerticies.size(); index++){
        if(edgeToCheck.city2 == foundVerticies[index]){
            return true;
        }
    }
    //else
    return false;
}

int bfs::calcTotalDist()
{
    int totalDist = 0;
    for(size_t index = 0; index < discEdges.size(); index++){
        totalDist += discEdges[index].weight;
    }

    return totalDist;
}

void bfs::printResults(){
    cout << "\nBFS:" << endl;
    cout << "*******************************************" << endl;
    for(size_t index = 0; index < foundVerticies.size(); index++) {
        cout << index << ": " << myGraph.getCityName(foundVerticies[index]) << endl;
    }

    cout << "\nDiscovery Edges" << endl;
    cout << "*******************************************" << endl;
    int totalDist = 0;
    for(size_t index = 0; index < discEdges.size(); index++){
        cout << myGraph.getCityName(discEdges[index].city1) << " to " << myGraph.getCityName(discEdges[index].city2) << endl;
        totalDist += discEdges[index].weight;
    }

    cout << "\nCross Edges" << endl;
    cout << "*******************************************" << endl;
    for(size_t index = 0; index < crossEdges.size(); index++){
        cout << myGraph.getCityName(crossEdges[index].city1) << " to " << myGraph.getCityName(crossEdges[index].city2) << endl;
    }

    cout << "\nTotal Distance on Discovery Edges: " << totalDist << endl;

}
