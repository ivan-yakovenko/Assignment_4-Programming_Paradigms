#include <iostream>

extern "C" {
    char* encrypt(char* rawText, int key) {
    for(int i = 0; i < strlen(rawText); i++) {
        if(isupper(rawText[i])) {
            rawText[i] = char(int((rawText[i] - 'A' + key + 26) % 26 + 'A'));
        }
        else if(islower(rawText[i])) {
            rawText[i] = char(int((rawText[i] - 'a' + key + 26) % 26 + 'a'));
        }
    }
    return rawText;
    }
    char* decrypt(char* encryptedText, int key) {
            return encrypt(encryptedText, -key);
    }
}
