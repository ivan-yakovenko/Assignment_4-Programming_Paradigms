#pragma once

extern "C" {
    typedef char* (*encrypt_func)(char*, int);
    typedef char* (*decrypt_func)(char*, int);
}

class CaesarCipher {
private:
    void* handle;
    encrypt_func encryptFunc;
    decrypt_func decryptFunc;
public:
    CaesarCipher();
    ~CaesarCipher();
    char* encrypt(char* rawText, int key);
    char* decrypt(char* encryptedText, int key);
};