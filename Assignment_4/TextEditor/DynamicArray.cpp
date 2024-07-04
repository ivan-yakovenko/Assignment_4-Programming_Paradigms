#include <iostream>
#include <fstream>
#include "DynamicArray.h"
#include "../CaesarCipher/CaesarCipher.h"
#include "../Text/Text.h"

using namespace std;

DynamicArray::DynamicArray() {
    rows = 0;
    cols = 0;
    capacity = 0;
    data = nullptr;
    buffer = nullptr;
}

DynamicArray::DynamicArray(char **data, size_t rows, size_t cols, size_t capacity, char *buffer) {
    this->rows = rows;
    this->cols = cols;
    this->capacity = capacity;
    this->data = data;
    this->buffer = buffer;
}

DynamicArray::~DynamicArray() {
    for (size_t i = 0; i < this->rows; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;
}

size_t DynamicArray::getCapacity() const {
    return this->capacity;
}

void DynamicArray::Resize(size_t newValueSize) {
    size_t oldCapacity = getCapacity();
    size_t newCapacity = oldCapacity + newValueSize;
    char **newData = new char *[newCapacity];

    for (size_t i = 0; i < oldCapacity; i++) {
        newData[i] = this->data[i];
    }

    for (size_t i = oldCapacity; i < newCapacity; i++) {
        newData[i] = new char[newCapacity];
    }

    delete[] this->data;

    this->data = newData;
    this->capacity = newCapacity;
}

void DynamicArray::PushBack(char *newValue) {

    size_t newValueLength = strlen(newValue);
    Resize(newValueLength);

    for (size_t i = 0; i < newValueLength; i++) {
        this->data[this->rows][this->cols] = newValue[i];
        this->cols++;
    }
    this->data[this->rows][this->cols] = '\0';
}

void DynamicArray::AddNewline() {
    PushBack(const_cast<char *>("\0"));
    this->rows++;
    this->cols = 0;
    char **newData = new char *[this->rows + 1];
    for (size_t i = 0; i < this->rows; ++i) {
        newData[i] = this->data[i];
    }
    newData[this->rows] = new char[this->capacity];
    newData[this->rows][0] = '\0';

    delete[] this->data;
    this->data = newData;
}

void DynamicArray::Insert(int line, int index, char *newValue) {
    if (line > this->rows) {
        cout << "Out of range, try another one" << endl;
        return;
    }

    int length = strlen(this->data[line]);
    if (index > length) {
        Resize(index - length + strlen(newValue));
        for (int i = 0; i < index; i++) {
            this->data[line][i] = ' ';
        }
    } else {
        Resize(strlen(newValue));
        memmove(&this->data[line][index + strlen(newValue)], &this->data[line][index], length - index + 1);
    };
    for (int k = 0; k < strlen(newValue); k++) {
        this->data[line][index + k] = newValue[k];
    }
    this->cols += strlen(newValue);
}

void DynamicArray::Search(char *text) {
    size_t textLength = strlen(text);
    int found;
    for (size_t i = 0; i <= this->rows; i++) {
        size_t rowLength = strlen(this->data[i]);
        for (size_t j = 0; j < rowLength; j++) {
            if (strncmp(&this->data[i][j], text, textLength) == 0) {
                printf("%zu, %zu\n", i, j);
                found = 1;
            }
        }
    }
    if (found == 0) {
        printf("Text not found");
    }
}

void DynamicArray::SaveInfo(char *filename) {
    ofstream fout(filename);
    for (size_t i = 0; i <= this->rows; i++) {
        size_t j = 0;
        while (this->data[i][j] != '\0') {
            fout << this->data[i][j];
            j++;
        }
        fout << endl;
    }
    fout.close();
}

void DynamicArray::LoadInfo(char *filename) {

    ifstream fin(filename);

    char element;

    while (fin.get(element)) {
        if (element == '\n') {
            AddNewline();
        } else {
            char str[2] = {element, '\0'};
            PushBack(str);
        }
    }
    fin.close();
}

void DynamicArray::Delete(int line, int index, int symbols) {
    if (line > this->rows) {
        cout << "Out of range, try another line" << endl;
        return;
    }

    int length = strlen(this->data[line]);
    if (index > length) {
        cout << "Out of range, try another index" << endl;
        return;
    }
    if (index + symbols > length) {
        cout << "Too many symbols to delete" << endl;
        return;
    }

    memmove(&this->data[line][index], &this->data[line][index + symbols], length - index - symbols + 1);
    this->cols -= symbols;

}

void DynamicArray::Cut(int line, int index, int symbols) {
    if (line > this->rows) {
        cout << "Out of range, try another line" << endl;
        return;
    }

    int length = strlen(this->data[line]);
    if (index > length) {
        cout << "Out of range, try another index" << endl;
        return;
    }
    if (index + symbols > length) {
        cout << "Too many symbols to delete" << endl;
        return;
    }

    if (buffer != nullptr) {
        delete[] buffer;
    }
    buffer = new char[symbols + 1];
    strncpy(buffer, &this->data[line][index], symbols);
    buffer[symbols] = '\0';

    memmove(&this->data[line][index], &this->data[line][index + symbols], length - index - symbols + 1);
    this->cols -= symbols;

}

void DynamicArray::Paste(int line, int index) {
    if (buffer == nullptr) {
        cout << "Nothing to paste" << endl;
        return;
    }
    Insert(line, index, buffer);
}

void DynamicArray::Copy(int line, int index, int symbols) {
    if (line > this->rows) {
        cout << "Out of range, try another line" << endl;
        return;
    }

    int length = strlen(this->data[line]);
    if (index > length) {
        cout << "Out of range, try another index" << endl;
        return;
    }
    if (index + symbols > length) {
        cout << "Too many symbols to delete" << endl;
        return;
    }

    if (buffer != nullptr) {
        delete[] buffer;
    }
    buffer = new char[symbols + 1];
    strncpy(buffer, &this->data[line][index], symbols);
    buffer[symbols] = '\0';
}

void DynamicArray::InsertReplacement(int line, int index, char *newValue) {
    if (line > this->rows) {
        cout << "Out of range, try another one" << endl;
        return;
    }

    int length = strlen(this->data[line]);

    if (index > length) {
        Resize(index - length + strlen(newValue));
        for (int i = 0; i < index; i++) {
            this->data[line][i] = ' ';
        }
    } else {
        Resize(strlen(newValue));
    };
    for (int k = 0; k < strlen(newValue); k++) {
        this->data[line][index+k] = newValue[k];
    }
    this->cols += strlen(newValue);
}

void DynamicArray::Print() const {
    for (size_t i = 0; i <= this->rows; i++) {
        size_t j = 0;
        while (this->data[i][j] != '\0') {
            cout << this->data[i][j];
            j++;
        }
        cout << endl;
    }
}

void DynamicArray::FileEncryption(char* inputFile, char* outputFile, int key) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);
    CaesarCipher caesar;
    Text text;

    char element;

    while (fin.get(element)) {
        text = element;
        char* encryptedText = caesar.encrypt(text.getText(), key);
        fout << encryptedText;
    }

    fin.close();
    fout.close();
}

void DynamicArray::FileDecryption(char* inputFile, char* outputFile, int key) {
    ifstream fin(inputFile);
    ofstream fout(outputFile);
    CaesarCipher caesar;
    Text text;

    char element;

    while (fin.get(element)) {
        text = element;
        char* decryptedText = caesar.decrypt(text.getText(), key);
        fout << decryptedText;
    }

    fin.close();
    fout.close();
}


void DynamicArray::Encrypt(int key) {
    CaesarCipher caesar;
    for (size_t i = 0; i <= this->rows; i++) {
        char *encryptedText = caesar.encrypt(this->data[i], key);
        this->data[i] = encryptedText;
    }
}

void DynamicArray::Decrypt(int key) {
    CaesarCipher caesar;
    for (size_t i = 0; i <= this->rows; i++) {
        char *decryptedText = caesar.decrypt(this->data[i], key);
        this->data[i] = decryptedText;
    }
}

void DynamicArray::ClearInfo(char *filename) {
    ofstream fout;
    fout.open(filename, ofstream::trunc);
    fout.close();
}

void DynamicArray::Run()  {
    while(true) {
        cout << "Choose the command: " << endl;
        int command;
        if (!(cin >> command)) {
            cout << "Enter valid command" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (command) {
            case 1 : {
                cout << "Enter text to append: " << endl;
                char *text = new char[256];
                cin.getline(text, 256);
                PushBack(text);
                delete[] text;
                break;
            }
            case 2: {
                AddNewline();
                cout << "New line is started" << endl;
                break;
            }
            case 3: {
                char filename[256];
                while(true) {
                    cout << "Enter the file name for saving: " << endl;
                    cin >> filename;
                    if(strstr(filename, ".txt") != nullptr) {
                        break;
                    }
                    cout << "Invalid file name, try again with '.txt' "<< endl;;
                }
                SaveInfo(filename);
                cout << "Text has been saved successfully" << endl;
                break;
            }
            case 4: {
                char filename[256];
                while(true) {
                    cout << "Enter the file name for loading: " << endl;
                    cin >> filename;
                    if(strstr(filename, ".txt") != nullptr) {
                        break;
                    }
                    printf("Invalid file name, try again with '.txt' \n");
                }
                LoadInfo(filename);
                cout << "Text has been loaded successfully" << endl;
                break;
            }
            case 5: {
                Print();
                cout << endl;
                break;
            }
            case 6: {
                cout << "Choose line and index: ";
                int line, index;
                cin >> line >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter text to insert: ";
                char *text = new char[256];
                cin.getline(text, 256);
                Insert(line, index, text);
                delete[] text;
                break;
            }
            case 7: {
                cout << "Enter text to search: ";
                char *text = new char[256];
                cin.getline(text, 256);
                Search(text);
                delete[] text;
                break;
            }
            case 8: {
                cout << "Choose line, index and number of symbols: ";
                int line, index, symbols;
                cin >> line >> index >> symbols;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Delete(line, index, symbols);
                break;
            }
            case 11: {
                cout << "Choose line, index and number of symbols: ";
                int line, index, symbols;
                cin >> line >> index >> symbols;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Cut(line, index, symbols);
                break;
            }
            case 12 : {
                cout << "Choose line and index: ";
                int line, index;
                cin >> line >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Paste(line, index);
                break;
            }
            case 13 : {
                cout << "Choose line and index and number of symbols: ";
                int line, index, symbols;
                cin >> line >> index >> symbols;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                Copy(line, index, symbols);
                break;
            }
            case 14: {
                cout << "Choose line and index: ";
                int line, index;
                cin >> line >> index;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Write text: ";
                char *text = new char[256];
                cin.getline(text, 256);
                InsertReplacement(line, index, text);
                delete[] text;
                break;
            }
            case 15: {
                string operation;
                while(true) {
                    cout << "Choose type of operation(encrypt/decrypt): ";
                    cin >> operation;
                    if(operation == "encrypt" || operation == "decrypt") {
                        break;
                    }
                    cout << "Invalid operation, try again "<< endl;;
                }

                char inputFile[256];

                while(true) {
                    cout << "Enter the input file path: ";
                    cin >> inputFile;
                    if(strstr(inputFile, ".txt") != nullptr) {
                        break;
                    }
                    cout << "Invalid file name, try again with '.txt' "<< endl;;
                }

                char outputFile[256];

                while(true) {
                    cout << "Enter the output file path: ";
                    cin >> outputFile;
                    if(strstr(outputFile, ".txt") != nullptr) {
                        break;
                    }
                    cout << "Invalid file name, try again with '.txt' "<< endl;;
                }

                cout << "Enter the key: ";
                int key;
                cin >> key;

                if(operation == "encrypt") {
                    FileEncryption(inputFile, outputFile, key);
                    cout << "Text has been encrypted successfully" << endl;
                }

                if(operation == "decrypt") {
                    FileDecryption(inputFile, outputFile, key);
                    cout << "Text has been decrypted successfully" << endl;
                }

                break;
            }
            case 16: {
                string operation;
                while(true) {
                    cout << "Choose type of operation(encrypt/decrypt): ";
                    cin >> operation;
                    if(operation == "encrypt" || operation == "decrypt") {
                        break;
                    }
                    cout << "Invalid operation, try again "<< endl;;
                }

                cout << "Enter the key: ";
                int key;
                cin >> key;

                if(operation == "encrypt") {
                    Encrypt(key);
                    cout << "Text has been encrypted successfully" << endl;
                }

                if(operation == "decrypt") {
                    Decrypt(key);
                    cout << "Text has been decrypted successfully" << endl;
                }

                break;
            }
            case 17: {
                char filename[256];
                while(true) {
                    cout << "Enter the file name for clearing: " << endl;
                    cin >> filename;
                    if(strstr(filename, ".txt") != nullptr) {
                        break;
                    }
                    cout << "Invalid file name, try again with '.txt' "<< endl;;
                }
                ClearInfo(filename);
                cout << "Text has been cleared successfully" << endl;
                break;
            }
            default: {
                cout << "Wrong command" << endl;
                break;
            }
        }

    }
}




//void DynamicArray::FileEncryption(char* inputFile, char* outputFile, int key) {
//    LoadInfo(inputFile);
//    CaesarCipher caesar;
//
//    char** newData = new char * [this->rows + 1];
//
//    for(size_t i = 0; i <= this->rows; i++) {
//        char* encryptedText = caesar.encrypt(this->data[i], key);
//        newData[i] = encryptedText;
//    }
//    for(size_t i = 0; i< this->rows; i++) {
//        delete[] this->data[i];
//    }
//    delete[] this->data;
//    this->data = newData;
//    SaveInfo(outputFile);
//}
//
//void DynamicArray::FileDecryption(char* inputFile, char* outputFile, int key) {
//    LoadInfo(inputFile);
//    CaesarCipher caesar;
//
//    char** newData = new char * [this->rows + 1];
//
//    for (size_t i = 0; i <= this->rows; i++) {
//        char *decryptedText = caesar.decrypt(this->data[i], key);
//        newData[i] = decryptedText;
//    }
//    for(size_t i = 0; i< this->rows; i++) {
//        delete[] this->data[i];
//    }
//    delete[] this->data;
//    this->data = newData;
//    SaveInfo(outputFile);
//}


//void DynamicArray::FileDecryption(char* inputFile, char* outputFile, int key) {
//    LoadInfo(inputFile);
//    CaesarCipher caesar;
//
//    for (size_t i = 0; i <= this->rows; i++) {
//        char *decryptedText = caesar.decrypt(this->data[i], key);
//        this->data[i] = decryptedText;
//    }
//
//    SaveInfo(outputFile);
//}