//
//  main.cpp
//  ISLab2
//
//  Created by Snow Lukin on 09.11.2022.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

void getSubCombinations(vector<int> arg, vector<int> codes, vector<vector<int>> &result) {
    for(int i = 0; i < codes.size(); i++) {
        vector<int> sub = arg;
        sub.push_back(codes[i]);
        result.push_back(sub);
        if (codes.size() > 0) {
            vector<int> newCodes;
            for(int j = i + 1; j < codes.size(); j++) {
                newCodes.push_back(sub[j]);
            }
            getSubCombinations(sub, newCodes, result);
        }
    }
}

vector<vector<int>> getCombinations(vector<int> codes) {
    vector<vector<int>> result;
    for(int i = 0; i < codes.size(); i++) {
        vector<int> temp;
        temp.push_back(codes[i]);
        result.push_back(temp);
        vector<int> newCodes;
        for(int j = i + 1; j < codes.size(); j++) {
            newCodes.push_back(codes[j]);
        }
        getSubCombinations(temp, newCodes, result);
    }
    return result;
}

void lab2task1() {
    string fileName("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab2_Input.txt"); // Change path
    vector<int> codes;
    int code;
    int numberToCrit;
    
    // Reading from file
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cout << "Could not open the file." << endl;
        return;
    }
    inputFile >> numberToCrit;
    while (inputFile >> code) {
        codes.push_back(code);
    }
    inputFile.close();
    
    vector<vector<int>> combinations = getCombinations(codes);
    vector<vector<int>> filteredCombinations;
    for(int i = 0; i < combinations.size(); i++) {
        int sum = 0;
        for(int j = 0; j < combinations[i].size(); j++) {
            sum += combinations[i][j];
        }
        if (sum % numberToCrit == 0) {
            filteredCombinations.push_back(combinations[i]);
        }
    }
    
    // Writing the results to the file
    ofstream outputFile("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab2_Output.txt"); // Change path
    if (!outputFile.is_open()) {
        cout << "Coult not open output file." << endl;
        return;
    }
    if (filteredCombinations.size() == 0) {
        cout << "NO" << endl;
        outputFile << "NO";
        outputFile.close();
        return;
    }
    outputFile << "YES\n";
    vector<int> chosenCombination = filteredCombinations[0];
    for(int i = 0; i < chosenCombination.size(); i++) {
        outputFile << chosenCombination[i] << " ";
    }
    outputFile << "\n" << pow(chosenCombination.size(), numberToCrit) << "\n";
    outputFile.close();
}

int main(int argc, const char * argv[]) {
    lab2task1();
    return 0;
}
