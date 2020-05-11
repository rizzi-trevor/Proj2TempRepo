#ifndef UNORDEREDMAP_H_
#define UNORDEREDMAP_H_

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * @brief Unordered map class
 * used to store data for trip algorithms
 * @author Jonathan Brubaker
 * @date December 2018
 */

const int MAP_SIZE = 42;

/**
* @author Jonathan Brubaker
* @brief Distance class, has name, diffrence and comparable operator
*/
struct Distance{
    string name;		//ending team name
    int diffrence;		//how far it is from originating team
    //enables sorting
    bool operator<(Distance rhs){return diffrence < rhs.diffrence;}
};

/**
* @author Jonathan Brubaker
* @brief stores a team using a team name, stadium and edges as well as
* a visited data type
*/
struct Team{
    string 			 teamName;	//starting team name
    string           stadium;   //teams staduim
    vector<Distance> dlist;	    //list of distances
    //vector<string>   souvenirs; //list of souvenirs
    bool 			 visited;	//used in algorithm
};
//end of special structs

/**
* @author Jonathan Brubaker
* @brief Key string with generic data type
*/
template <class t>
struct keyMap{
        t      data;
        string key;
};

/**
* @author Jonathan Brubaker
* @brief stores all information utalized in the trip algorithms
*/
template <class t>
class unorderedMap{
private:
        vector<vector<keyMap<t>>> map;//buckets to catch all the stuff

        int ocupied;		         //how many buckets are occupied
        int size;			         //how many elements are in the map
public:
        unorderedMap():map(MAP_SIZE), size(0), ocupied(0){}

        int  getSize()   {return size;}
        int  getOcupied(){return ocupied;}
        bool isFull() 	 {return ocupied == map.size();}
        bool isEmpty()	 {return size == 0;}

        /**
        * @author Jonathan Brubaker
        * @brief creates a pointer list of all objects
        * @return vector<t*> of all elements
        * @param NA
        */
        vector<t*> createList(){
                vector<t*> elements;

                for(int i = 0; i < map.size(); i++){
                        for(int j = 0; j < map[i].size(); j++){
                                elements.push_back(&map[i][j].data);
                        }
                }

                return elements;
        }
        /**
        * @author Jonathan Brubaker
        * @brief creates a has int to pass into hash map
        * @return int, hash number
        * @param string& key string used as a key
        */
        int hash(string& key){
                int hashNum   = 0;    //number that does the hash thing

                for(int i = 0; i < key.length(); i++){
                        hashNum += (int)key[i];
                }

                return hashNum %= MAP_SIZE;
        }
        /**
        * @author Jonathan Brubaker
        * @brief adds a new element to a hash map
        * @return NA
        * @param string key, t element, element and key used for map
        */
        void add(string key, t element){
                keyMap<t> temp;
                temp.data = element;
                temp.key  = key;

                bool isUnique = true; //checks if key is unique.
                int hashNum   = hash(key);

                if(map[hashNum].size() == 0){
                        map[hashNum].push_back(temp);

                        size++;
                        ocupied++;
                }
                else{
                        for(int i = 0; i < map[hashNum].size(); i++){
                                if(map[hashNum][i].key == key){
                                        isUnique = false;
                                        break;
                                }
                        }

                        if(isUnique){
                                map[hashNum].push_back(temp);
                                size++;
                        }
                        else{
                                cout << "\nERROR, KEY ALREADY EXISTS\n";
                        }
                }
        }
        /**
        * @author Jonathan Brubaker
        * @brief returns pointer to object data in map
        * @return t*
        * @param string key, key used to find item in map
        */
        t* find(string key){
                int  i;
                bool found  = false;
                int hashNum = hash(key);

                for(i = 0; i < map[hashNum].size(); i++){
                        if(map[hashNum][i].key == key){
                                found = true;
                                break;
                        }
                }

                if(found){
                        return &map[hashNum][i].data;
                }
                else{
                        cout << "\nERROR, KEY NOT FOUND\n";
                }

                return nullptr;
        }
};



#endif /* UNORDEREDMAP_H_ */
