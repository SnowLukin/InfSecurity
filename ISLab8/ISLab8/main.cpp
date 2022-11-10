//
//  main.cpp
//  ISLab8
//
//  Created by Snow Lukin on 10.11.2022.
//

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <set>
#include <sstream>
#include <math.h>

using namespace std;


struct cell {
    int subj_i;
    int obj_j;
    string value;
};

struct cells {
    vector<cell> v;
    vector <int> deleteList;
    int n;
    int m;
};

string ruleSetGen() {
    string M = "rw";
    int n = pow(2, M.size());
    static vector <string> fullRuleSet;
    if (fullRuleSet.size() == 0) {
        for (int i = 0; i < n; i++) {
            string buff = "";
            for (int j = 0; j < M.size(); j++) {
                if (i & (1 << j)) {
                    buff += M[j];
                }
            }
            fullRuleSet.push_back(buff);
        }
        fullRuleSet[0] = "_";
    }
    string ruleSet = fullRuleSet[rand() % 4];
    return ruleSet;
}

void output(cells Cells) {
    cout << endl << "( subject object rule )" << endl;
    cout << endl;
    for (int i = 0; i < Cells.v.size(); i++) {
        cout << Cells.v[i].subj_i+1 << " " << Cells.v[i].obj_j + 1 << " " << Cells.v[i].value << endl;
    }
    cout << endl;
}

void clearEmpty(cells& Cells) {
    for (int d = 0; d < Cells.v.size(); d++) {
        if (Cells.v[d].value == "") {
            Cells.v.erase(Cells.v.begin() + d);
        }
    }
}

void changeRule(cells& Cells) {
    cout << "Edit cell" << endl;
    int act, i, j;
    cout << "delete - 1, add - 2" << endl;
    cin >> act;
    string rule;
    cout << "Rule Subject Object" << endl;
    cin >> rule >> i >> j;
    i--; j--;

    bool f = false;
    for (int d = 0; d < Cells.v.size(); d++) {
        if (Cells.v[d].subj_i == i && Cells.v[d].obj_j == j && act == 1) {
            string res = rule;
            for (int inputInd = 0; inputInd < res.size(); inputInd++) {
                for (int nowInd = 0; nowInd < Cells.v[d].value.size(); nowInd++) {
                    if (res[inputInd] == Cells.v[d].value[nowInd]) {
                        Cells.v[d].value = Cells.v[d].value.substr(0, nowInd) + Cells.v[d].value.substr(nowInd + 1, Cells.v[d].value.size() - nowInd - 1);
                        break;
                    }
                }
            }
            f = true;
            break;
        }
        if (Cells.v[d].subj_i == i && Cells.v[d].obj_j == j && act == 2) {
            string res = rule;
            for (int inputInd = 0; inputInd < res.size(); inputInd++) {
                bool f = true;
                for (int nowInd = 0; nowInd < Cells.v[d].value.size(); nowInd++) {
                    if (res[inputInd] == Cells.v[d].value[nowInd]) {
                        f = false;
                        break;
                    }
                }
                if (f) {
                    Cells.v[d].value += res[inputInd];
                }
            }
            f = true;
            break;
        }
    }
    if (!f && act == 2 && Cells.n > i && find(Cells.deleteList.begin(), Cells.deleteList.end(), i) == Cells.deleteList.end()) {
        cell temp;
        temp.subj_i = i;
        temp.obj_j = j;
        temp.value = rule;
        Cells.v.push_back(temp);
    } else {
        cout << "Failed performing command" << endl;
    }
}

void insertNewSubj(cells& Cells) {
    cell temp;
    temp.subj_i = Cells.n;
    Cells.n += 1;
    cout << "New Object Index: " << Cells.n << endl;
}

void deleteSubj(cells& Cells) {
    int del_subj_i;
    cout << "Object Index: " << endl;
    cin >> del_subj_i;
    del_subj_i--;

    bool isOneOrMore = false;
    bool finded = true;
    while (finded) {
        finded = false;
        for (int i = 0; i < Cells.v.size(); i++) {
            if (Cells.v[i].subj_i == del_subj_i) {
                finded = true;
                Cells.v.erase(Cells.v.begin() + i);
                isOneOrMore = true;
                break;
            }
        }
    }
    
    if (!isOneOrMore) {
        cout << "Failed finding object" << endl;
    } else {
        Cells.deleteList.push_back(del_subj_i);
    }
}

void task4(cells& Cells) {
    int max_index_i = -1;
    for (int i = 0; i < Cells.v.size(); i++)
        if (Cells.v[i].subj_i > max_index_i)
            max_index_i = Cells.v[i].subj_i;
    max_index_i++;
    cout << "Matrix Size (n x m) :" << max_index_i << "x" << Cells.m << endl;
    cout << "Cells:" << max_index_i * Cells.m << endl;
    cout << "Filled Cells:" << Cells.v.size() << endl;
    float all = max_index_i * Cells.m;
    float items_size = Cells.v.size();
    cout << "Filled status:" << float((items_size / all) * 100) << "%" << endl;
}

void task5(cells& Cells) {
    cout << "Object index: " << endl;
    int obj_index;
    cin >> obj_index;
    obj_index--;

    vector <int> answer = vector <int>();
    for (int i = 0; i < Cells.v.size(); i++)
    {
        if (!(find(answer.begin(), answer.end(), Cells.v[i].subj_i) != answer.end()) && Cells.v[i].obj_j == obj_index)
            answer.push_back(Cells.v[i].subj_i);
    }
    cout << "Subjects with access to the object: " << endl;
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << endl;
    }
}

cells getRazrMatr() {
    int n = rand() % 10 + 2; // число субъектов(программ обработчиков) n
    int m = rand() % 10 + 2; // число объектов(содержат информацию) m

    cells Cells;
    Cells.v = vector<cell>();
    Cells.deleteList = vector<int>();
    Cells.n = n;
    Cells.m = m;

    for (int i = 0; i < n; i++) // строки-субъекты
    {
        for (int j = 0; j < m; j++) // столбцы-объекты
        {
            string temp_RW = ruleSetGen();
            if (temp_RW != "_") {
                cell temp_item;
                temp_item.subj_i = i;
                temp_item.obj_j = j;
                temp_item.value = temp_RW;
                Cells.v.push_back(temp_item);
            }
        }
    }
    return Cells;
}

void doInterpretationLoop(cells Items) {
    cout << "<< Commands List >>" << endl;
    cout << "0 - Exit" << endl;
    cout << "1 - Edit Cell" << endl;
    cout << "2 - Add new Subject" << endl;
    cout << "3 - Delete Subject" << endl;
    cout << "4 - Filled Status(total/stored)" << endl;
    cout << "5 - Subjects with access to the Object X" << endl;

    int Inp;
    do {
        cout << "Command: ";
        cin >> Inp;
        if (Inp == 1) {
            changeRule(Items);
        }
        if (Inp == 2) {
            insertNewSubj(Items);
        }
        if (Inp == 3) {
            deleteSubj(Items);
        }
        if (Inp == 4) {
            task4(Items);
        }
        if (Inp == 5) {
            task5(Items);
        }

        clearEmpty(Items);
        output(Items);
    } while (Inp != 0);
}


int main(int argc, const char * argv[]) {
//    srand(time(0));
    
    cells Items = getRazrMatr();
    output(Items);

    doInterpretationLoop(Items);
    return 0;
}
