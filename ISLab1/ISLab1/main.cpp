//
//  main.cpp
//  ISLab1
//
//  Created by Snow Lukin on 09.11.2022.
//

#include <iostream>
#include <sstream>
#include <math.h>
#include <fstream>
#include <string>

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

int main(int argc, const char * argv[]) {
    lab1task1();
}
