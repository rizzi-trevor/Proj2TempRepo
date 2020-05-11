#include "graphinfo.h"
#include "ui_graphinfo.h"

graphInfo::graphInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphInfo)
{
    ui->setupUi(this);

    int bfsValue = performBFS();
    int dfsValue = performDFS();
    int mstValue = performMST();

    ui->bfsLabel->setText(QString::number(bfsValue));
    ui->dfsLabel->setText(QString::number(dfsValue));
    ui->mstLabel->setText(QString::number(mstValue));



}

graphInfo::~graphInfo()
{
    delete ui;
}

void graphInfo::onCloseClick()
{
    this->hide();
}


QStringList convertTeamNamesToStadiumNames(QStringList teamsSelected) {
    QStringList temp;

    QSqlQuery searchQuery;
    for(int i = 0; i < teamsSelected.size(); i++) {
        searchQuery.prepare("SELECT DISTINCT StadiumName FROM MLB WHERE TeamName = :teamName");   /// finds the corresponding stadium name
        searchQuery.bindValue(":teamName", teamsSelected.at(i));
        searchQuery.first();
        qDebug() << searchQuery.exec();

        qDebug() << "teamsSelected: " << teamsSelected.at(i);
        while(searchQuery.next()) {
//          qDebug() << "STADIUM CONVERTED: " << searchQuery.value(0).toString();
            temp.push_back(searchQuery.value(0).toString());                                                /// adds the stadium names to a list
        }
    }

    return temp;        /// returns the stadium name list
}

int performDijkstra(QStringList teamsSelected, QString ID)
{
    QString lastStadium;
    int last;
    DbManager myDb = DbManager(PROJECT_PATH + "/college.db");
    graphAdjList graph; /// Graph object.
    int totalDistance = 0;

    cout << endl << "ADDING TO GRAPH/VERTICES:" << endl;

    //QStringList temp = convertTeamNamesToStadiumNames(teamsSelected);
    QStringList temp = teamsSelected;

    for(int i = 0;i < temp.size(); i++) {
        qDebug() << "CONVERTED TEAM NAMES: " << temp.at(i);
    }

    QSqlQuery getCityInfo;
    getCityInfo.prepare("SELECT * FROM Distances"); ///Load getCityInfo with current city info
    getCityInfo.exec();

    while(getCityInfo.next()) {

        graph.insertEdge(getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               /// Add edge from starting stadium >> ending stadium

        graph.insertEdge(getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               /// Add edge from ending stadium >> starting stadium (because undirected)
    }
    vector<string> dijkstra;    /// vector string of stadium names

    int costs[graph.size()];
    int parent[graph.size()];

    for(int i = 0; i < temp.size() - 1; i++) {
       graph.shortestPathsDijkstra(temp.at(i).toStdString(), dijkstra, costs, parent);
        cout << "DESTINATION (A to B): " << temp.at(i).toStdString() << " to " << temp.at(i + 1).toStdString() << endl;
        cout << "COUNT: " << i << endl;

        vector<string> path =  graph.returnPath(temp.at(i).toStdString(), temp.at(i + 1).toStdString(), parent);

        cout << "PATH: ";

        for(unsigned int j = 0; j < path.size(); j++) {
            cout << path[j];

            if(j + 1 != path.size())
            {
                cout << " to ";
            }
        }

        cout << endl;
        cout << "Total Distance: " << costs[graph.findVertex(temp.at(i + 1).toStdString())] << endl << endl;
        totalDistance += costs[graph.findVertex(temp.at(i + 1).toStdString())];
        int tempDist = costs[graph.findVertex(temp.at(i + 1).toStdString())];

         myDb.addTrip(ID, temp.at(i), i, tempDist);

         lastStadium = temp.at(i + 1);

         dijkstra.clear();
         last = i + 1;

    }
    myDb.addTrip(ID, lastStadium, last, 0);

    cout << endl;
    cout << "TOTAL DISTANCE: " << totalDistance << endl;

    return totalDistance;
}


int performMST() {
graphAdjList graph; /// Graph object.

 cout << endl << "ADDING TO GRAPH/VERTICES:" << endl;

    QSqlQuery getCityInfo;
    getCityInfo.prepare("SELECT * FROM Distances"); ///Load getCityInfo with current city info
    getCityInfo.exec();

    while(getCityInfo.next()) {

        graph.insertEdge(getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               /// Add edge from starting stadium >> ending stadium

        graph.insertEdge(getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               /// Add edge from ending stadium >> starting stadium (because undirected)
    }

    vector<string> MST;

    cout << endl;
    cout << "MST edges + weight" << endl;
    cout << "****************************" << endl;

    int mstDistance = graph.primJarnikMST("Safeco Field", MST);

    cout << "Total Distance : " << mstDistance << endl;

    return mstDistance;
}

int performBFS() {
    graph myGraph; /// Graph object.

    cout << endl << "ADDING VERTICIES TO GRAPH:" << endl;

    QSqlQuery getCityNames;
    getCityNames.prepare("SELECT StadiumName FROM MLB ORDER BY TeamName");
    getCityNames.exec();

    while(getCityNames.next())
    {
        cout << getCityNames.value(0).toString().toStdString() << endl;
        myGraph.addCity(getCityNames.value(0).toString().toStdString());
    }

    cout << "ADDING EDGES TO GRAPH\n";

    QSqlQuery getCityInfo;
    getCityInfo.prepare("SELECT * FROM Distances"); ///Load getCityInfo with current city info
    getCityInfo.exec();

    while(getCityInfo.next()) {

        qDebug() << getCityInfo.value(0).toString();
        myGraph.addEdges(getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               ///Add edge from starting stadium >> ending stadium
    }
    vector<string> BFSsearch;    /// vector string of stadium names

    getCityInfo.first();

    bfs mySearch(myGraph);
    int totalDistance = mySearch.startSearch("Target Field");

    return totalDistance; /// Returns totalDistance to be output within UI
}

int performDFS() {
    dfsGraph dfsGraph; /// dfsGraph object.

    cout << endl << "ADDING TO dfsGraph/VERTICES:" << endl;

    QSqlQuery getCityInfo;
    getCityInfo.prepare("SELECT * FROM Distances"); ///Load getCityInfo with current city info
    getCityInfo.exec();

    while(getCityInfo.next()) {

        dfsGraph.insertEdge(getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               ///Add edge from starting stadium >> ending stadium

        dfsGraph.insertEdge(getCityInfo.value(1).toString().toStdString(),
                         getCityInfo.value(0).toString().toStdString(),
                         getCityInfo.value(2).toInt()  );               ///Add edge from ending stadium >> starting stadium (because undirected)
    }
    vector<string> DFSsearch;    /// vector string of stadium names



    getCityInfo.first();

    // DFS Search and total distance calculated
    getCityInfo.prepare("SELECT begStadium FROM Distances WHERE begStadium = 'AT&T Park'");
    getCityInfo.exec();
    getCityInfo.next();
    cout << endl <<"DFS - STARTING AT " << getCityInfo.value(0).toString().toStdString() << endl;       ///Output the starting stadium

    int totalDistance = dfsGraph.DFS(getCityInfo.value(0).toString().toStdString(), DFSsearch);            ///Perform DFS to find total distance

    for(unsigned int i = 0; i < DFSsearch.size(); i++)
    {
        cout << DFSsearch.at(i) << endl;
    }

    cout << "Total Distance Traveled by Discovery Edges: " << totalDistance << endl;    ///Output total distance

    return totalDistance; /// Returns totalDistance to be output within UI
}

