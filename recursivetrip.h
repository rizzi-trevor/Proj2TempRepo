#ifndef RECURSIVETRIP_H
#define RECURSIVETRIP_H

#include "unorderedMap.h"

class Trip{
private:
    vector<string> teamsNames;
    vector<string> sortedTeams;

    vector<Team*> teams; ///vector of team pointers

    unorderedMap<Team>* map; //pointer to a map

    int teamCount; //if user selects visit a certain number of cities
    int totalDistance;
public:
    int getDistance(){return totalDistance;}
    vector<string> getFinalTrip(){return sortedTeams;}

    Trip(vector<string> &teamList, unorderedMap<Team>& um, int numTeams = 0){
        teamsNames = teamList;
        map = &um;
        teamCount = numTeams == 0 ? teamsNames.size() : numTeams;
        //makes it so we know to look for the teams
        for(int i = 0; i < teamsNames.size(); i++){
            map->find(teamsNames[i])->visited = false;
        }

        teams = map->createList();

        totalDistance = 0;
    }

    /**
        * @author Jonathan Brubaker
        * @brief runs the trip algorithm
        * @return NA
        */
    void takeTrip()
    {
        bool notComplete = false; //break;

        sortedTeams.push_back(teamsNames.front());
        map->find(teamsNames.front())->visited = true;
        //vector<int> cost = dijkstra(teamsNames.front());
        teamsNames.erase(teamsNames.begin());


        for(int i = 0; i < teamsNames.size(); i++)
        {
            if(map->find(sortedTeams.back())->stadium == map->find(teamsNames[i])->stadium)
            {
                map->find(teamsNames[i])->visited = true;
                swap(teamsNames[0], teamsNames[i]);
                sortedTeams.push_back(teamsNames.front());
                teamsNames.erase(teamsNames.begin());
            }
        }



        vector<int> cost = dijkstra(sortedTeams.back());

        //		while(notComplete){
        //			notComplete = false;
        int distance = 10000000;
        int di;//distance index
        for(int i = 0; i < cost.size(); i++){
            if(!teams[i]->visited && cost[i] < distance){
                di = i;
                distance = cost[i];

                notComplete = true;
            }
        }

        //wooops
        bool notFound = true;
        int i = 0;
        while(notFound && i < teamsNames.size()){
            if(teams[di]->teamName == teamsNames[i]){
                di = i;
                notFound = false;
            }
            i++;
        }

        if(notComplete){
            totalDistance += distance;
            swap(teamsNames[0], teamsNames[di]);//makes it so new emelent is at front
            cerr << "next team" <<  teamsNames[0] << " " << distance << " distance" << endl;
            takeTrip();
        }
        //		}
    }

    /**
        * @author Jonathan Brubaker
        * @brief runs the dijkstra algorithm
        * @return vector<int> of team traversal costs
        * @param string startingCity
        */
    vector<int> dijkstra(string startingCity){
        vector<int> costs;
        vector<int> parent;
        vector<int> currentNodes;

        int i;
        int j;

        for(i = 0; i < teams.size(); i++){
            costs.push_back(1000000);//arbitrarily high number
            parent.push_back(-1);
            //verticies[i].visited = false;
        }

        currentNodes.push_back(findIndex(map->find(startingCity)->stadium));
        costs[currentNodes.front()] = 0;
        while(currentNodes.size() != 0)
        {
            int sz = currentNodes.size();
            for(i = 0; i < sz; i++)
            {
                for(j = 0; j < teams[currentNodes.front()]->dlist.size(); j++)
                {
                    int index = findIndex(teams[currentNodes.front()]->dlist[j].name);
                    if(teams[currentNodes.front()]->dlist[j].diffrence + costs[currentNodes.front()]< costs[index])
                    {
                        costs[index] = teams[currentNodes.front()]->dlist[j].diffrence + costs[currentNodes.front()];

                        parent[index] = currentNodes.front();

                        currentNodes.push_back(index);
                    }
                }
                currentNodes.erase(currentNodes.begin());
            }
        }

        while(j != -1)
        {
            cout << '\t' << teams[parent[j]]->teamName << endl;
            j = parent[j];
        }

        return costs;
    }

    int findIndex(string team){
        int index = 0;
        while(index < teams.size() && teams[index]->stadium != team){index++;}// && teams[index]->visited){index ++;}

        return index;
    }
};


#endif // RECURSIVETRIP_H
