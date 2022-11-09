//
//  main.cpp
//  ISLab3
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

vector<string> generateGrayCode(int n) {
    if (n == 0) {
        return {"0"};
    } else if (n == 1) {
        return {"0", "1"};
    }
    
    vector<string> prevN = generateGrayCode(n - 1);
    vector<string> result;
    
    for (int i = 0; i < prevN.size(); i++) {
        string s = prevN[i];
        result.push_back("0" + s);
    }
    
    for (int i = prevN.size() - 1; i >= 0; i--) {
        string s = prevN[i];
        result.push_back("1" + s);
    }
    return result;
}

void lab3task1() {
    int n;
    cout << "N: ";
    cin >> n;
    
    string fileName("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab3_Output.txt"); // Change path
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        cout << "Failed opening the file." << endl;
        return;
    }
    
    vector<string> result = generateGrayCode(n);
    
    for (int i = 0; i < result.size(); i++) {
        outputFile << result[i] << " ";
    }
}

int main(int argc, const char * argv[]) {
    lab3task1();
    return 0;
}
