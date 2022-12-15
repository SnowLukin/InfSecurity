//
//  main.cpp
//  LSLab12
//
//  Created by Snow Lukin on 08.12.2022.
//

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "functions.hpp"
#include "longest.hpp"

using namespace std;

struct RsaEncrypter {
private:
    ulongest e = 0, n = 0;

public:
    RsaEncrypter(ulongest e, ulongest n) {
        this->e = e;
        this->n = n;
    }
    
    ulongest encrypt(ulongest message) {
        return pow(message, n, e);
    }
};

struct RsaDecrypter {
private:
    ulongest d = 0, n = 0;
    
public:
    RsaDecrypter(ulongest d, ulongest n) {
        this->d = d;
        this->n = n;
    }
    
    ulongest decrypt(ulongest message) {
        return pow(message, n, d);
    }
};

struct ElGamalEncrypter {
private:
    ulongest y = 0, g = 0, p = 0;
    
public:
    ElGamalEncrypter(ulongest y, ulongest g, ulongest p) {
        this->y = y;
        this->g = g;
        this->p = p;
    }
    
    pair<ulongest, ulongest> encrypt(ulongest message) {
        ulongest k = getEasy(p - 1);
        return pair<ulongest, ulongest>(pow(g, p, k), (pow(y, p, k) * message) % p);
    }
};

struct ElGamalDecrypter {
private:
    ulongest x = 0, p = 0;
    
public:
    ElGamalDecrypter(ulongest x, ulongest p) {
        this->x = x;
        this->p = p;
    }
    
    ulongest decrypt(pair<ulongest, ulongest> message) {
        return (message.second * pow(message.first, p, p - 1 - x)) % p;
    }
};

pair<RsaEncrypter, RsaDecrypter> RsaGenerate(ulongest p, ulongest q) {
    ulongest n = p * q;
    ulongest nEiler = (p - 1) * (q - 1);
    ulongest e = getEasy(nEiler);
    ulongest d = getD(e, nEiler);

    return pair<RsaEncrypter, RsaDecrypter>(RsaEncrypter(e, n), RsaDecrypter(d, n));
}

pair<ElGamalEncrypter, ElGamalDecrypter> ElGamalGenerate(ulongest p) {
    ulongest g = getG(p);
    ulongest x = rand() % (p.toInt() - 1) + 1;
    ulongest y = pow(g, p, x);

    return pair<ElGamalEncrypter, ElGamalDecrypter>(ElGamalEncrypter(y, g, p), ElGamalDecrypter(x, p));
}

void RsaExample() {
    ulongest p = 5, q = 7;
    
    pair<RsaEncrypter, RsaDecrypter> rsa = RsaGenerate(p, q);
    
    cout << "RSA:" << endl;
    
    ulongest message = 24;
    cout << "Message: " << message.toInt() << endl;

    ulongest encryptedMessage = rsa.first.encrypt(message);
    cout << "Encrypted message: " << encryptedMessage.toInt() << endl;

    ulongest dectyptedMessage = rsa.second.decrypt(encryptedMessage);
    cout << "Decrypted message: " << dectyptedMessage.toInt() << endl;
    cout << endl;

}

void ElGamalExample() {
    ulongest p = 997;
    
    pair<ElGamalEncrypter, ElGamalDecrypter> elGamal = ElGamalGenerate(p);
    
    cout << "ElGamal:" << endl;

    ulongest message = 234;
    cout << "Message: " << message.toInt() << endl;

    pair<ulongest, ulongest> encryptedMessage = elGamal.first.encrypt(message);
    cout << "Encrypted message: (" << encryptedMessage.first.toInt() << ", " << encryptedMessage.second.toInt() << ")" << endl;
    
    ulongest decryptedMessage = elGamal.second.decrypt(encryptedMessage);
    cout << "Decrypted message: " << decryptedMessage.toInt() << endl;
}

int main() {
    RsaExample();
    ElGamalExample();
}
