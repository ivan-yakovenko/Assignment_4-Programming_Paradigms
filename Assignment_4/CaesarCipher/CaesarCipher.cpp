#include "CaesarCipher.h"
#include <iostream>
#include <dlfcn.h>

using namespace std;

CaesarCipher::CaesarCipher() {
    handle = dlopen("./mylib.so", RTLD_LAZY);

    if(!handle) {
        cout << "Error" << dlerror() << endl;
        return;
    }

    encryptFunc = reinterpret_cast<encrypt_func>(dlsym(handle, "encrypt"));
    if(!encryptFunc) {
        cout << "Error with encrypt" << dlerror() << endl;
        return;
    }

    decryptFunc = reinterpret_cast<decrypt_func>(dlsym(handle, "decrypt"));
    if(!decryptFunc) {
        cout << "Error with decrypt" << dlerror() << endl;
        return;
    }
}

CaesarCipher::~CaesarCipher() {
    if (handle) {
        dlclose(handle);
    }
}

char *CaesarCipher::encrypt(char* rawText, int key) {
    if (encryptFunc) {
        return encryptFunc(rawText, key);
    }
    return nullptr;
}

char *CaesarCipher::decrypt(char *encryptedText, int key) {
    if(decryptFunc) {
        return decryptFunc(encryptedText, key);
    }
    return nullptr;
}