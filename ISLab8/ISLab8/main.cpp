//
//  main.cpp
//  ISLab8
//
//  Created by Snow Lukin on 10.11.2022.
//

#include <iostream>
#include <vector>
#include <set>
#include <string.h>

using namespace std;

class Matrix {
private:
    vector<vector<pair<int, set<string>>>> values;
    int w, h;
    
public:
    Matrix(int w, int h) {
        this->values = vector<vector<pair<int, set<string>>>>(h, vector<pair<int, set<string>>>());
        this->w = w;
        this->h = h;
    }
    
    int getWidth() {
        return w;
    }
    
    int getHeight() {
        return h;
    }
    
    set<string> get(int objIndex, int subjIndex) {
        if (objIndex < 0 || objIndex >= w || subjIndex < 0 || subjIndex >= h) { return set<string>(); }
        
        for(int i = 0; i < values[subjIndex].size(); i++) {
            if (values[subjIndex][i].first == objIndex) return values[subjIndex][i].second;
        }
        
        return set<string>();
    }
    
    void changeRule(int objIndex, int subjIndex, string rule, bool isRemoving) {
        if (objIndex < 0 || objIndex >= w || subjIndex < 0 || subjIndex >= h) { return; }
        
        for(int i = 0; i < values[subjIndex].size(); i++) {
            if (values[subjIndex][i].first == objIndex) {
                if (isRemoving) {
                    values[subjIndex][i].second.erase(rule);
                    
                    if (values[subjIndex][i].second.size() == 0) {
                        values[subjIndex].erase(values[subjIndex].begin() + i);
                    }
                } else {
                    values[subjIndex][i].second.insert(rule);
                }
                return;
            }
        }
        
        if (!isRemoving) {
            values[subjIndex].push_back(pair<int, set<string>>(objIndex, set<string>()));
            values[subjIndex][values[subjIndex].size() - 1].second.insert(rule);
        }
    }
    
    void addObject(string name) {
        values.push_back(vector<pair<int, set<string>>>());
        h++;
        cout << "Object " + name + " was registered with id " << h << endl;
    }
    
    void addSubject(string name) {
        w++;
        cout << "Subject " + name + " was registered with id " << w << endl;
    }
    
    void deleteObject(int at) {
        values[at] = vector<pair<int, set<string>>>();
    }
    
    void deleteSubject(int at) {
        for (int i = 0; i < values.size(); i++) {
            for(int j = 0; j < values[i].size(); j++) {
                if (values[i][j].first == at) {
                    values[i].erase(values[i].begin() + j);
                }
            }
        }
    }
    
    float precent() {
        float totalCount = w * h;
        float currentCount = 0;
        for(int i = 0; i < values.size(); i++) {
            currentCount += values[i].size();
        }
        
        return currentCount / totalCount;
    }
    
    set<int> hasRule(int objIndex) {
        set<int> result = set<int>();
        
        for(int i = 0; i < values[objIndex].size(); i++) {
            result.insert(values[objIndex][i].first);
        }
        
        return result;
    }
    
    void print() {
        for(int objIndex = 0; objIndex < h; objIndex++) {
            for(int subjIndex = 0; subjIndex < w; subjIndex++) {
                set<string> rules = get(objIndex, subjIndex);
                
                if (rules.size() == 0) {
                    cout << "{ } ";
                } else {
                    cout << "{ ";
                    for(set<string>::iterator i = rules.begin(); i != rules.end(); i++) {
                        cout << *i << " ";
                    }
                    cout << "} ";
                }
            }
            cout << endl;
        }
    }
};

class ChinaWall {
public:
    // фирма - набор объектов
    vector<set<int>> firms;

    // конфликт интересов - набор фирм
    vector<set<int>> iterestConflicts;

    // история запросов для субъектов - список из последовательностей запросов каждого субъекта
    // запрос - индекс объекта + тип запроса
    vector<vector<pair<int, string>>> accessSubjectHistory;

    // история запросов для объектов - список из последовательностей запросов каждого объекта
    // запрос - индекс субъекта + тип запроса
    vector<vector<pair<int, string>>> accessObjectHistory;

private:
    vector<string> split(string line) {
        vector<string> result = vector<string>();

        for(int i = 0; i < line.size(); i++) {
            if(line[i] == ' ') {
                result.push_back(line.substr(0, i));
                vector<string> tail = split(line.substr(i + 1, line.size() - i - 1));
                result.insert(result.end(), tail.begin(), tail.end());
                break;
            }
        }

        if (result.size() == 0) {
            result.insert(result.begin(), line);
        }

        return result;
    }

    int getInterestGroup(int forObject) {
        int firm = getFirm(forObject);

        for(int i = 0; i < iterestConflicts.size(); i++) {
            if(iterestConflicts[i].contains(firm)) {
                return i;
            }
        }

        return -1;
    };

    int getFirm(int forObject) {
        for(int i = 0; i < firms.size(); i++) {
            if (firms[i].contains(forObject)) {
                return i;
            }
        }
        return -1;
    }

    void printFirmObjects(int firmIndex) {
        for(set<int>::iterator i = firms[firmIndex].begin(); i != firms[firmIndex].end(); i++) {
            cout << *i << ", ";
            i++;
        }
        cout << endl;
    }

    void printReportForSubject(int subjectIndex) {
        for(int i = 0; i < accessSubjectHistory[subjectIndex].size(); i++) {
            cout << "access " << accessSubjectHistory[subjectIndex][i].second << " with object " << accessSubjectHistory[subjectIndex][i].first << " in firm " << getFirm(accessSubjectHistory[subjectIndex][i].first);
        }
    }

    void printReportForObject(int objectIndex) {
        for(int i = 0; i < accessObjectHistory[objectIndex].size(); i++) {
            cout << "access " << accessObjectHistory[objectIndex][i].second << " with object " << accessObjectHistory[objectIndex][i].first << " in firm " << getFirm(accessObjectHistory[objectIndex][i].first);
        }
    }

    bool canRead(int subjectIndex, int objectIndex) {
        int interestGroup = getInterestGroup(objectIndex);
        int objectFirm = getFirm(objectIndex);

        set<int> accessGroups = set<int>();
        set<int> firmGroups = set<int>();

        for(int i = 0; i < accessSubjectHistory[subjectIndex].size(); i++) {
            accessGroups.insert(getInterestGroup(accessSubjectHistory[subjectIndex][i].first));
            firmGroups.insert(getFirm(accessSubjectHistory[subjectIndex][i].first));
        }

        return !accessGroups.contains(interestGroup) || firmGroups.contains(objectFirm);
    }

    bool canWrite(int subjectIndex, int objectIndex) {
        int objectFirm = getFirm(objectIndex);
        int objectInterest = getInterestGroup(objectIndex);
        bool isReadFromAnoutherFirm = false;

        set<int> readedFirms = set<int>();

        for(int i = 0; i < accessSubjectHistory[subjectIndex].size(); i++) {
            if (accessSubjectHistory[subjectIndex][i].second == "r" &&
                getFirm(accessSubjectHistory[subjectIndex][i].first) != objectFirm &&
                getInterestGroup(accessSubjectHistory[subjectIndex][i].first) == objectInterest) {
                isReadFromAnoutherFirm = true;
                break;
            }
        }

        return canRead(subjectIndex, objectIndex) && !isReadFromAnoutherFirm;
    }

    void read(int subjectIndex, int objectIndex) {
        if (canRead(subjectIndex, objectIndex)) {
            accessSubjectHistory[subjectIndex].push_back(pair<int, string>(objectIndex, "r"));
            accessObjectHistory[objectIndex].push_back(pair<int, string>(subjectIndex, "r"));
            cout << "accepted" << endl;
        } else {
            cout << "refused" << endl;
        }
    }

    void write(int subjectIndex, int objectIndex) {
        if (canWrite(subjectIndex, objectIndex)) {
            accessSubjectHistory[subjectIndex].push_back(pair<int, string>(objectIndex, "w"));
            accessObjectHistory[objectIndex].push_back(pair<int, string>(subjectIndex, "w"));
            cout << "accepted" << endl;
        } else {
            cout << "refused" << endl;
        }
    }

public:
    ChinaWall(int objCount, int subjCount, int firmCount, int interCount) {
        this->firms = vector<set<int>>(firmCount, set<int>());
        this->iterestConflicts = vector<set<int>>(interCount, set<int>());

        this->accessSubjectHistory = vector<vector<pair<int, string>>>(subjCount);
        this->accessObjectHistory = vector<vector<pair<int, string>>>(objCount);
    }

    void execute(string command) {
        vector<string> words = split(command);

        if (words[0] == "start") {
            accessSubjectHistory = vector<vector<pair<int, string>>>(accessSubjectHistory.size());
            accessObjectHistory = vector<vector<pair<int, string>>>(accessObjectHistory.size());
        } else if (words[0] == "read") {
            int subjectIndex = stoi(words[1]);
            int objectIndex = stoi(words[2]);
            read(subjectIndex, objectIndex);
        } else if (words[0] == "write") {
            int subjectIndex = stoi(words[1]);
            int objectIndex = stoi(words[2]);
            write(subjectIndex, objectIndex);
        } else if (words[0] == "report_subject") {
            int subjectIndex = stoi(words[1]);
            printReportForSubject(subjectIndex);
        } else if (words[0] == "report_object") {
            int objectIndex = stoi(words[1]);
            printReportForObject(objectIndex);
        } else if (words[0] == "brief_case") {
            int firmIndex = stoi(words[1]);
            printFirmObjects(firmIndex);
        } else {
            cout << "invalid command" << endl;
        }

        cout << endl;
    }
};

int main() {

    ChinaWall wall = ChinaWall(6, 1, 3, 2); // objectCount, subjectCount, firmCount, conflictoOfInterestCount
    
    // firms 0: { 0, 1, 2 }
    wall.firms[0].insert(0);
    wall.firms[0].insert(1);
    wall.firms[0].insert(2);

    // firms 1: { 3, 4}
    wall.firms[1].insert(3);
    wall.firms[1].insert(4);

    // firms 2: { 5 }
    wall.firms[2].insert(5);

    //interest conflicts 0: { f0, f1 }
    wall.iterestConflicts[0].insert(0);
    wall.iterestConflicts[0].insert(1);

    //interest conflicts 1: { f2 }
    wall.iterestConflicts[1].insert(2);

    // reading test
    
    cout << "test 1:" << endl;
    // subjIndex - objIndex
    wall.execute("read 0 0"); // accepted
    wall.execute("read 0 3"); // error - object is in different firm and in confict of interest
    wall.execute("read 0 5"); // accepted - different conflict of interest

    cout << "test 2:" << endl;
    wall.execute("start");
    wall.execute("read 0 3"); // accepted
    wall.execute("read 0 4"); // accepted - conflict of interests but same firm

    cout << "test 3:" << endl;
    wall.execute("start");
    wall.execute("write 0 0"); // ок
    wall.execute("write 0 1"); // ок - объект в той же фирме
    wall.execute("write 0 3"); // ошибка - объект в другой фирме и в том же конфликте интересов
    wall.execute("write 0 5"); // ок - объект в другой фирме, но в другом конфликте интересов

    return 0;
}
