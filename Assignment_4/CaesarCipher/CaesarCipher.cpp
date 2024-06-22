#include "CaesarCipher.h"
#include <iostream>
#include <dlfcn.h>

using namespace std;

CaesarCipher::CaesarCipher() {
    handle = nullptr;
    encryptFunc = nullptr;
    decryptFunc = nullptr;
}

CaesarCipher::CaesarCipher(char *library) {
    handle = dlopen(library, RTLD_LAZY);

    if(!handle) {
        cout << "Error" << dlerror() << endl;
        return;
    }

    encryptFunc = reinterpret_cast<encrypt_func>(dlsym(handle, "encrypt"));
    if(!encryptFunc) {
        cout << "Error with encrypt" << dlerror() << endl;
        return;
    }

    decryptFunc = reinterpret_cast<encrypt_func>(dlsym(handle, "decrypt"));
    if(!decryptFunc) {
        cout << "Error with decrypt" << dlerror() << endl;
        return;
    }
}

CaesarCipher::~CaesarCipher() {
    if(handle) {
        dlclose(handle);
    }
}

char *CaesarCipher::encrypt(char *rawText, int key) {
    for(int i = 0; i < strlen(rawText); i++) {
        key = (key % 26 + 26) % 26;
        if(isupper(rawText[i])) {
            rawText[i] = char(int((rawText[i] - 'A' + key + 26) % 26 + 'A'));
        }
        else if(islower(rawText[i])) {
            rawText[i] = char(int((rawText[i] - 'a' + key + 26) % 26 + 'a'));
        }
    }
    return rawText;
}

char *CaesarCipher::decrypt(char *encryptedText, int key) {
    return encrypt(encryptedText, -key);
}