#pragma once

class CaesarCipher {
private:
    void* handle;
    typedef char* (*encrypt_func)(char*, int);
    typedef char* (*decrypt_func)(char*, int);
    encrypt_func encryptFunc;
    decrypt_func decryptFunc;
public:
    CaesarCipher();
    CaesarCipher(char* library);
    ~CaesarCipher();
    char* encrypt(char* rawText, int key);
    char* decrypt(char* encryptedText, int key);
};