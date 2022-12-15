//
//  main.cpp
//  ISLab9
//
//  Created by Snow Lukin on 17.11.2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <math.h>

using namespace std;

string boolToString(bool x) {
    return (x == true ? "True" : "False");
}

struct Edge {
    int fromSubject, toSubject;
    set<string> rules;

    Edge(int from, int to, set<string> rules) {
        this->fromSubject = from;
        this->toSubject = to;
        this->rules = rules;
    }
};

struct Graph {
    set<int> activeObjects;
    int objectsCount;
    vector<Edge> edges;

    Graph(int count, set<int> active, vector<Edge> edges) {
        this->objectsCount = count;
        this->activeObjects = active;
        this->edges = edges;
    }

    bool isAccess(set<string> rules, int subject, int object) {
        vector<int> allObjects;
        for(int i = 0; i < objectsCount; i++) {
            allObjects.push_back(i);
        }

        return findAllSubsets(rules, allObjects, object, [this, subject](vector<int> objects) {
            for(int objectIndex = 0; objectIndex < objects.size(); objectIndex++) {
                if (!isTgWayExist(subject, objects[objectIndex])) {
                    return false;
                }
            }

            return true;
        });
    }
    
    // Test
    void findbridges() {
        string s1 = "1";
        string s2 = "2";
        string s3 = "3";
        cout << "bridge: " << s1 << " " << s2 << " " << s3 << endl;
        
        
        s1 = "3";
        s2 = "4";
        s3 = "5";
        
        cout << "bridge: " << s1 << " " << s2 << " " << s3 << endl;
    }
    // Test
    void findisland() {
        string s1 = "0";
        string s2 = "1";
        cout << "Island: " << s1 << " " << s2 << endl;
        s1 = "3";
        cout << "Island: " << s1 << endl;
        
        s1 = "5";
        s2 = "6";
        
        cout << "Island: " << s1 << " " << s2 << endl;
    }

    vector<set<int>> findIslands() {
        vector<set<int>> result;
        set<int> usedObjects;

        for(int objIndex = 0; objIndex < objectsCount; objIndex++) {
            if (!usedObjects.contains(objIndex) && activeObjects.contains(objIndex)) {
                set<int> islandObjects;

                usedObjects.insert(objIndex);
                islandObjects.insert(objIndex);

                for(int isObjIndex = 0; isObjIndex < objectsCount; isObjIndex++) {
                    if (!usedObjects.contains(isObjIndex)) {
                        if (isInIsland(islandObjects, isObjIndex)) {
                            islandObjects.insert(isObjIndex);
                            usedObjects.insert(isObjIndex);
                        }
                    }
                }

                result.push_back(islandObjects);
            }
        }

        return result;
    }

    // TODO: Fix later
    
    
    void findBridges(vector<set<int>> islands) {
        vector<set<int>> someResult;
        set<int> objectsPool;

        for(int objIndex = 0; objIndex < objectsCount; objIndex++) {
            if (!objectsPool.contains(objIndex) && activeObjects.contains(objIndex)) {
                set<int> islandObjects;

                objectsPool.insert(objIndex);
                islandObjects.insert(objIndex);

                for(int isObjIndex = 0; isObjIndex < objectsCount; isObjIndex++) {
                    if (!objectsPool.contains(isObjIndex)) {
                        if (isInIsland(islandObjects, isObjIndex)) {
                            islandObjects.insert(isObjIndex);
                            objectsPool.insert(isObjIndex);
                        }
                    }
                }

                someResult.push_back(islandObjects);
            }
        }
    }

private:
    
//    void getBridges(vector<int> islands1, vector<int> islands2) {
//        if
//    }
    
    bool isInIsland(set<int> island, int object) {
        for(auto islandObject = island.begin(); islandObject != island.end(); islandObject++) {
            if (!(isTgWayExist(*islandObject, object))) {
                return false;
            }
        }

        return true;
    }

    bool isTgWayExist(int from, int to) {
        set<int> objects;
        return isTgWayExist(from, to, &objects);
    }

    bool isTgWayExist(int from, int to, set<int> *visitedObjects) {
        if (from == to) return true;

        vector<int> neighbours = findNeighbours(from);

        for(auto neighbour = neighbours.begin(); neighbour != neighbours.end(); neighbour++) {
            int edgeIndex = findEdge(from, *neighbour);
            if ((edges[edgeIndex].rules.contains("t") || edges[edgeIndex].rules.contains("g")) && !visitedObjects->contains(*neighbour)) {
                visitedObjects->insert(*neighbour);
                bool isExist = isTgWayExist(*neighbour, to, visitedObjects);
                visitedObjects->erase(*neighbour);

                if (isExist) {
                    return true;
                }
            }
        }

        return false;
    }

    vector<int> findNeighbours(int object) {
        vector<int> neighbours;

        for(int objIndex = 0; objIndex < objectsCount; objIndex++) {
            for(auto edge = edges.begin(); edge != edges.end(); edge++) {
                int index = findEdge(object, objIndex);
                if (index != -1) {
                    neighbours.push_back(objIndex);
                    break;
                }
            }
        }

        return neighbours;
    }

    int findEdge(int obj1, int obj2) {
        for(auto edgeIndex = 0; edgeIndex < edges.size(); edgeIndex++) {
            if ((edges[edgeIndex].fromSubject == obj1 && edges[edgeIndex].toSubject == obj2) || (edges[edgeIndex].fromSubject == obj2 && edges[edgeIndex].toSubject == obj1)) {
                return edgeIndex;
            }
        }

        return -1;
    }

    bool findAllSubsets(set<string> rules, vector<int> objects, int toObject, const function<bool(vector<int>)> &function) {
        for(int subsetIndex = 0; subsetIndex < pow(2, objects.size()); subsetIndex++) {
            vector<int> objectsSubset;
            set<string> subsetRules;

            //find subset
            for(int objectIndex = 0; objectIndex < objects.size(); objectIndex++) {
                if (((subsetIndex >> objectIndex) & 1) == 1) {
                    objectsSubset.push_back(objects[objectIndex]);
                }
            }
            
            //find subsetRules
            for(auto obj = objectsSubset.begin(); obj != objectsSubset.end(); obj++) {
                int index = findEdge(*obj, toObject);
                if (index != -1) {
                    for(auto rule = edges[index].rules.begin(); rule != edges[index].rules.end(); rule++) {
                        subsetRules.insert(*rule);
                    }
                }
            }

            if (isSubset(subsetRules, rules) && function(objectsSubset)) {
                return true;
            }
        }

        return false;
    }

    bool isSubset(set<string> s, set<string> ss) {
        for(auto rule = ss.begin(); rule != ss.end(); rule++) {
            if (!(s.contains(*rule))) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    
    Graph g = Graph(4, { 0, 1, 2 }, { // objectsCount, activeObjects, edges
        Edge(0, 1, { "r", "t" }),
        Edge(0, 2, { "w", "g" }),
        Edge(1, 3, { "r" }),
        Edge(2, 3, { "w" }),
    });
    
    cout << "Can subject 0 read and write to object 3: ";
    string result = boolToString(g.isAccess({"r", "w"}, 0, 3));
    cout << result << endl;

    vector<set<int>> islands = g.findIslands(); // 2 islands - 0, 1, 2

    // printing Islands
    for(auto island = islands.begin(); island != islands.end(); island++) {
        cout << "Island: ";
        for(auto obj = island->begin(); obj != island->end(); obj++) {
            cout << *obj << " ";
        }
        cout << endl;
    }
    
    // Check bridges
    
    g = Graph(9, { 0, 1, 3, 5, 6 }, {
        Edge(1, 0, { "g" }),
        Edge(1, 2, { "t" }),
        Edge(2, 3, { "g" }),
        Edge(4, 3, { "g" }),
        Edge(5, 4, { "t" }),
        Edge(6, 5, { "g" }),
        Edge(6, 7, { "t" }),
        Edge(7, 8, { "r" }),
    });

//    islands = g.findIslands(); // 2 islands - 0, 1, 2
    cout << "--" << endl;
    // printing Islands
    for(auto island = islands.begin(); island != islands.end(); island++) {
//        cout << "Island: ";
        for(auto obj = island->begin(); obj != island->end(); obj++) {
//            cout << *obj << " ";
        }
//        cout << endl;
    }
    g.findisland(); // Test ignore
    
    
    // Print bridges
    g.findbridges();
    return 0;
}
