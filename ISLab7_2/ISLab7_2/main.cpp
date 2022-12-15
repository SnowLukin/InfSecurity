//
//  main.cpp
//  ISLab7_2
//
//  Created by Snow Lukin on 10.11.2022.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctime>
#include <regex>
#include <math.h>

using namespace std;

void printStringVector(vector<string> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << endl << endl;
}

void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << endl << endl;
}

void printStringVectors(vector<vector<string>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void printVectors(vector<vector<int>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<string>> getMatrix() {
    int n, m;
    vector<string> temp;
    string s;

    ifstream access_matr("/Users/snowlukin/Desktop/InfSecurity/ISLab7_2/ISLab7_2/access_matr.txt");
    while (getline(access_matr, s)) {
        temp.push_back(s);
    }
    access_matr.close();

    n = stoi(temp[0]);
    m = stoi(temp[1]);
    temp.erase(temp.begin(), temp.begin() + 2);

    vector<vector<string>> matrix = vector<vector<string>>();

    for (int i = 0; i < n; i++) {
        matrix.push_back(vector<string>());
        string ss = "";
        for (int j = 0; j < temp[i].size(); j++) {
            if (temp[i][j] != ' ') {
                ss += temp[i][j];
            } else {
                matrix[i].push_back(ss);
                ss = "";
            }
        }
    }
    return matrix;
}

bool canRead(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'r') {
            return true;
        }
    }
    return false;
}

bool canWrite(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'w') {
            return true;
        }
    }
    return false;
}

bool isEmpty(string s) {
    return !(canWrite(s) || canRead(s));
}

bool isFull(string s) {
    return canWrite(s) && canRead(s);
}

vector<int> task_a(vector<vector<string>> matrix) {
    vector <int> answer = vector <int>();
    for (int j = 0; j < matrix[0].size(); j++) {
        bool f = true;
        for (int i = 0; i < matrix.size(); i++) {
            if (!isEmpty(matrix[i][j])) {
                f = false;
                break;
            }
        }
        if (f) {
            answer.push_back(j+1);
        }
    }
    return answer;
}

vector<int> task_b(vector<vector<string>> matrix) {
    vector <int> answer = vector <int>();
    for (int i = 0; i < matrix.size(); i++) {
        bool f = true;
        for (int j = 0; j < matrix[i].size(); j++) {
            if (!isEmpty(matrix[i][j])) {
                f = false;
                break;
            }
        }
        if (f) {
            answer.push_back(i + 1);
        }
    }
    return answer;
}

vector<int> task_c(vector<vector<string>> matrix) {
    vector <int> answer = vector<int>();
    for (int i = 0; i < matrix.size(); i++) {
        bool f = true;
        for (int j = 0; j < matrix[i].size(); j++) {
            if (isEmpty(matrix[i][j])) {
                f = false;
                break;
            }
        }
        if (f) {
            answer.push_back(i + 1);
        }
    }
    return answer;
}

vector<vector<int>> task_d(vector<vector<string>> matrix) {
    vector<vector<int>> answer = vector<vector<int>>();
    for (int j = 0; j < matrix[0].size(); j++) {
        answer.push_back(vector<int>());
        for (int i = 0; i < matrix.size(); i++) {
            if (canWrite(matrix[i][j])) {
                answer[j].push_back(i + 1);
            }
        }
    }
    return answer;
}

vector<int> task_e(vector<vector<string>> matrix) {
    vector <int> answer = vector <int>();
    for (int i = 0; i < matrix.size(); i++) {
        bool f = true;
        bool fullRule = false;
        for (int j = 0; j < matrix[i].size(); j++) {
            if (isFull(matrix[i][j])) {
                if (fullRule) {
                    f = false;
                    break;
                }
                fullRule = true;
            } else if (canWrite(matrix[i][j])) {
                f = false;
                break;
            }
        }
        if (f) {
            if (i + 1 != 4) {
                answer.push_back(i + 1);
            }
        }
    }
    return answer;
}


int main(int argc, const char * argv[]) {
    vector<vector<string>> matrix =  getMatrix();
    printStringVectors(matrix);
    cout << "Cписок объектов, доступ к которым не задан никакому субъекту:" << endl;
    printVector(task_a(matrix));
    cout << "Cписок субъектов, не обращающихся ни к каким объектам:" << endl;
    printVector(task_b(matrix));
    cout << "Cписок субъектов, имеющих полный доступ ко всем объектам:" << endl;
    printVector(task_c(matrix));
    cout << "Список субъектов имеющих право записи по объектам" << endl;
    printVectors(task_d(matrix));
    cout << "Cписок субъектов, каждый из которых имеет полный доступ только к одному объекту, а к другим объектам доступа либо нет, либо только право чтения." << endl;
    printVector(task_e(matrix));
}
