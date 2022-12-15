//
//  main.cpp
//  ISLab6
//
//  Created by Snow Lukin on 09.11.2022.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <set>
#include <string>
#include <ctime>
using namespace std;

void printVector(vector<int> vect) {
    for(int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << endl;
}

void print3DArray(vector<vector<vector<int>>> array3d) {
    for(int x = 0; x < array3d.size(); x++) {
        for(int y = 0; y < array3d[x].size(); y++) {
            cout << "( ";
            for(int z = 0; z < array3d[x][y].size(); z++) {
                cout << array3d[x][y][z];
                if (z != array3d[x][y].size() - 1) {
                    cout << ", ";
                }
            }
            cout << " )  ";
        }
        cout << endl;
    }
}

vector<vector<vector<int>>> writeCorrectRights(vector<vector<vector<int>>> megamatrix, vector<int> ls, vector<int> lo, int n, int m) {
    vector<vector<vector<int>>> newMatrix = megamatrix;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            vector<int> rw = {0, 0};
            if (ls[i] >= lo[j]) {
                rw[0] = 1;
            }
            if (ls[i] <= lo[j]) {
                rw[1] = 1;
            }
            newMatrix[j][i] = rw;
        }
    }
    return newMatrix;
}

vector<vector<vector<int>>> writeRightsA(vector<vector<vector<int>>> megamatrix, int n, int m) {
    vector<vector<vector<int>>> newMatrix = megamatrix;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int first = rand() % 2;
            int second = first == 0 ? 1 : rand() % 2;
            newMatrix[j][i] = {first, second};
        }
    }
    return newMatrix;
}

vector<vector<vector<int>>> generateInput(int n, int m, bool random) {
    
    vector<int> ls;
    vector<int> lo;
    for(int i = 0; i < n; i++) {
        ls.push_back(rand() % n);
    }
    for(int i = 0; i < m; i++) {
        lo.push_back(rand() % m);
    }
    vector<vector<vector<int>>> megamatrix;
    for(int i = 0; i < m; i++) {
        megamatrix.push_back({});
        for(int j = 0; j < n; j++) {
            megamatrix[i].push_back({0});
        }
    }
    if (random) {
        return writeRightsA(megamatrix, n, m);
    }
    return writeCorrectRights(megamatrix, ls, lo, n, m);
}

bool checkRights(vector<vector<vector<int>>> A, int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (A[j][i][0] == 1 && A[j][i][1] == 1) {
                return false;
            }
        }
    }
    return true;
}

void createLsLo(vector<vector<vector<int>>> A, int n, int m) {
    vector<int> ls(n);
    vector<int> lo(m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (A[j][i][0] == 1) {
                ls[i] += 1;
            }
            if (A[j][i][1] == 1) {
                lo[j] += 1;
            }
        }
    }
    cout << "ls" << endl;
    printVector(ls);
    cout << "l0" << endl;
    printVector(lo);
}

void lab6task1() {
    int n = 3;
    int m = 2;
    vector<vector<vector<int>>> A;
    A = generateInput(n, m, true);
    cout << checkRights(A, n, m) << endl;
}

void lab6task2() {
    int n = 3;
    int m = 2;
    vector<vector<vector<int>>> A;
    A = generateInput(n, m, true);
    print3DArray(A);
    createLsLo(A, n, m);
}

int main(int argc, const char * argv[]) {
//    lab6task1();
    lab6task2();
    return 0;
}
