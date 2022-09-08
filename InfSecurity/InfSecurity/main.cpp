//
//  main.cpp
//  InfSecurity
//
//  Created by Snow Lukin on 08.09.2022.
//

#include <iostream>
#include <sstream>
using namespace std;



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

int main(int argc, const char * argv[]) {
    string sentence = "ethingSom  ethingSom ethingSom";
    decode(sentence);
    return 0;
}
