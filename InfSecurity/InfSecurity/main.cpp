//
//  main.cpp
//  InfSecurity
//
//  Created by Snow Lukin on 08.09.2022.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;

// MARK: - Lab 1
string moveCharToLeft(string word) {
    word.insert(0, 1, word[word.length() - 1]);
    word.erase(word.length() - 1, 1);
    return word;
}

string decodeWord(string word) {
    for (int i = 0; i < 3; i++) {
        word = moveCharToLeft(word);
    }
    return word;
}

void decode(string sentence) {
    string resultSentence = "";
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        resultSentence += decodeWord(word) + " ";
    }
    cout << resultSentence << endl;
}

void lab1task1() {
    string sentence = "ethingSom  ethingSom ethingSom";
    decode(sentence);
}

// MARK: - Lab 2
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
    string fileName("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab2_Input.txt");
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
    ofstream outputFile("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab2_Output.txt");
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

// MARK: - Lab 3

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
    
    string fileName("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab3_Output.txt");
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


// MARK: - Lab 4

void printVector(vector<int> vect) {
    for(int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << endl;
}

bool isPrime(int number) {
    if (number == 0 || number == 1) {
        return false;
    }
    for (int i = 2; i < number / 2; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

vector<int> getPrimeFactors(int number) {
    vector<int> result;
    result.push_back(1);
    
    int div = 2;
    while (number > 1) {
        while (number % div == 0) {
            result.push_back(div);
            number = number / div;
        }
        div++;
    }
    return result;
}

long factorial(const int n) {
    long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    return factorial;
}

int getAmountOfPermutations(vector<int> numbers) {
    vector<int> uniqueNumbers = numbers;
    uniqueNumbers.erase(unique(uniqueNumbers.begin(), uniqueNumbers.end()), uniqueNumbers.end());
    
    vector<int> repeatedAmounts;
    for (int i = 0; i < uniqueNumbers.size(); i++) {
        int counter = count(numbers.begin(), numbers.end(), uniqueNumbers[i]);
        if (counter > 1) {
            repeatedAmounts.push_back(counter);
        }
    }
    int repeatedMult = 1;
    for (int i = 0; i < repeatedAmounts.size(); i++) {
        repeatedMult *= factorial(repeatedAmounts[i]);
    }
    return factorial(numbers.size()) / repeatedMult;
}

int getNumberFromVector(vector<int> digits) {
    int sum = 0;
    int multiplier = pow(10, digits.size() - 1);
    for (int i = 0; i < digits.size(); i++) {
        sum += digits[i] * multiplier;
        multiplier /= 10;
    }
    return sum;
}

vector<int> getFourDigitVector(vector<int> vect) {
    vector<int> result;
    result.assign(vect.begin(), vect.begin() + 4);
    vect.erase(vect.begin(), vect.begin() + 4);
    
    for(int i = 0; i < vect.size(); i++) {
        for(int j = result.size() - 1; j >= 0; j--) {
            if (result[j] * vect[i] < 10) {
                result[j] *= vect[i];
                break;
            }
        }
    }
    for(int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return result;
}

void lab4task1() {
    int number = 243;
    
    vector<int> primeFactors = getPrimeFactors(number);
    
    printVector(primeFactors);
    
    vector<int> primeFactorsWithoutOne;
    primeFactorsWithoutOne.assign(primeFactors.begin() + 1, primeFactors.end());
    
    cout << "primeFactorsWithoutOne" << endl;
    printVector(primeFactorsWithoutOne);
    
    vector<int> codeWithoutOne = getFourDigitVector(primeFactorsWithoutOne);
    if (isPrime(getNumberFromVector(codeWithoutOne))) {
        int permutationCount = getAmountOfPermutations(codeWithoutOne);
        
        cout << "Permutations: " << permutationCount << endl;
        return;
    }
    vector<int> codeWithOne = getFourDigitVector(primeFactors);
    if (isPrime(getNumberFromVector(codeWithOne))) {
        int permutationCount = getAmountOfPermutations(codeWithOne);
        vector<vector<int>> primePermVector;
        do {
            if (isPrime(getNumberFromVector(codeWithOne))) {
                primePermVector.push_back(codeWithOne);
            }
            //                printVector(codeWithOne);
        } while (next_permutation(codeWithOne.begin(), codeWithOne.end()));
        
        string fileName("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab4_Output.txt");
        ofstream outputFile(fileName);
        
        outputFile << primePermVector.size() << "\n";
        
        for(int i = 0; i < primePermVector.size(); i++) {
            for(int j = 0; j < primePermVector[i].size(); j++) {
                outputFile << primePermVector[i][j] << " ";
            }
            outputFile << "\n";
        }
        
        return;
    }
    cout << "Counldnt find prime code" << endl;
}



// MARK: - Main Function
int main(int argc, const char * argv[]) {
    //    lab1task1();
    //    lab2task1();
    //    lab3task1();
    lab4task1();
    return 0;
}
