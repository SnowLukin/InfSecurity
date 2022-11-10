//
//  main.cpp
//  ISLab7
//
//  Created by Snow Lukin on 09.11.2022.
//

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <set>
#include <sstream>

using namespace std;

vector<vector<set<string>>> A; // матрица прав доступа
int n, m;

void createObject(int at) {
    vector<set<string>> v(m, set<string>());
    for(unsigned i = 0; i < m; i++) {
        v.insert(v.begin() + i, {"ro"}); // Could be anything
    }
    A.insert(A.begin() + at, v);
}

void destroyObject(int at) {
    A[at] = vector<set<string>>(m, set<string>());
}

void createSubject(int at) {
    for (int i = 0; i < A.size(); i++) {
        set<string> sub = {"ro"}; // Could be anything
        
        A[i].insert(A[i].begin() + at, sub);
    }
}

void destroySubject(int at) {
    for (int i = 0; i < A.size(); i++) {
        A[i][at] = set<string>();
    }
}

void enterP(int o, int s, string v) {
    if (!A[o][s].contains(v)) {
        A[o][s].insert(v);
    }
}

void deleteP(int o, int s, string v) {
    if (A[o][s].contains(v)) {
        A[o][s].erase(v);
    }
}

bool constaint(vector<string> arr, string v) {
    for(int i = 0; i < arr.size(); i++) {
        if (arr[i] == v) {
            return true;
        }
    }
    return false;
}

vector<string> split(string str, char ch = ' ') {
    vector<string> words;
    string word = "";
    for (auto x : str) {
        if (x == ch) {
            words.push_back(word);
            word = "";
        } else {
            word = word + x;
        }
    }
    words.push_back(word);
    return words;
}

void printVector(vector<string> v) {
    for(int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void execute(string command) {
    
    if (command.substr(7, 2) == "O+") {
        vector<string> args = split(command);
        string indexWord = args[3];
        int index = stoi(indexWord.substr(6, command.size() - 7));
        createObject(index);
    } else if (command.substr(7, 2) == "O-") {
        vector<string> args = split(command);
        string indexWord = args[3];
        int index = stoi(indexWord.substr(6, command.size() - 7));
        destroyObject(index);
    } else if (command.substr(7, 2) == "S+") {
        vector<string> args = split(command);
        string indexWord = args[3];
        int index = stoi(indexWord.substr(6, command.size() - 7));
        createSubject(index);
    } else if (command.substr(7, 2) == "S-") {
        vector<string> args = split(command, ' ');
        string indexWord = args[3];
        int index = stoi(indexWord.substr(6, command.size() - 7));
        destroySubject(index);
    } else {
        vector<string> args = split(command);
        
        if (args[0] == "if") {
            int x = stoi(args[6].substr(6, 1));
            int y = stoi(args[7].substr(6, 1));

            if (A[x][y].contains(args[1])) {
                string newCommand = "";
                newCommand += args[9];
                newCommand += " = ";
                newCommand += args[5];
                newCommand += " ";
                newCommand += args[6];
                newCommand += " ";
                newCommand += args[7];

                execute(newCommand);
            }
        } else {
            int x = stoi(args[3].substr(6, 1));
            int y = stoi(args[4].substr(6, 1));
            
            if (args[2].substr(2,1) == "+") {
                enterP(x, y, args[2].substr(1, 1));
            } else {
                deleteP(x, y, args[2].substr(1, 1));
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream environFile("/Users/snowlukin/Desktop/InfSecurity/ISLab7/ISLab7/environ.txt");
    string environLine;
    
    getline(environFile, environLine);
    n = stoi(environLine);
    getline(environFile, environLine);
    m = stoi(environLine);
    
    cout << "n: " << n << ", m: " << m << endl;
    A = vector<vector<set<string>>>(n);

    for(int i = 0; i < n; i++) {
        A[i] = vector<set<string>>(m, set<string>());
    }

    for(int x = 0; x < n; x++) {
        getline(environFile, environLine);
        vector<string> splittedLine;
        splittedLine = split(environLine);
        for(int y = 0; y < m; y++) {
            A[x][y] = set<string>();
            A[x][y].insert(splittedLine[y]);
        }
    }
    environFile.close();
    cout << endl;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            set<string> subset = A[i][j];
            ostringstream stream;
            copy(subset.begin(), subset.end(), ostream_iterator<string>(stream, " "));
            string result = stream.str();
            cout << result;
        }
        cout << endl;
    }
    
    ifstream prgrmFile("/Users/snowlukin/Desktop/InfSecurity/ISLab7/ISLab7/prgrm.txt");
    string prgrmLine;
    
    while(getline(prgrmFile, prgrmLine)) {
        execute(prgrmLine);
    }
    prgrmFile.close();
    
    ofstream rzltFile("/Users/snowlukin/Desktop/InfSecurity/ISLab7/ISLab7/rzlt.txt");
    string rzltLine;
    
    for(int i = 0; i < A.size(); i++) {
        rzltLine = "";
        for(int j = 0; j < A[i].size(); j++) {
            set<string> subset = A[i][j];
            ostringstream stream;
            copy(subset.begin(), subset.end(), ostream_iterator<string>(stream, " "));
            string result = stream.str();
            rzltLine += result;
        }
        rzltFile << rzltLine;
        if (rzltLine != "") {
            rzltFile << "\n";
        }
    }
    rzltFile.close();
        
    return 0;
}
