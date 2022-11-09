//
//  main.cpp
//  ISLab4
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
        
        string fileName("/Users/snowlukin/Desktop/InfSecurity/InfSecurity/InfSecurity/Lab4_Output.txt"); // Change path
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

int main(int argc, const char * argv[]) {
    lab4task1();
    return 0;
}
