#include <iostream>
#include "CaesarCipher/CaesarCipher.h"
using namespace std;

int main() {
    CaesarCipher caesar("./mylib.so");

    char text[] = "Roses are red, violets are blue";
    char* encryptedText = caesar.encrypt(text, 2);
    cout << "Encrypted text: " << encryptedText << endl;

    char* decryptedText = caesar.decrypt(encryptedText, 2);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}