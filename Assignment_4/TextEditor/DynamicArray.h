#pragma once
#include <iostream>

class DynamicArray {
private:
    char** data;
    size_t rows;
    size_t cols;
    size_t capacity;
    char* buffer;
public:
    DynamicArray();
    DynamicArray(char** data, size_t rows, size_t cols, size_t capacity, char* buffer);
    ~DynamicArray();
    size_t getCapacity() const;
    void Resize(size_t newValueSize);
    void PushBack(char* newValue);
    void AddNewline();
    void Insert(int line, int index, char *newValue);
    void Search(char* text);
    void SaveInfo(char* filename);
    void LoadInfo(char* filename);
    void Delete(int line, int index, int symbols);
    void Cut(int line, int index, int symbols);
    void Paste(int line, int index);
    void Copy(int line, int index, int symbols);
    void InsertReplacement(int line, int index, char *newValue);
    void Print() const;
    void Run();
    void FileEncryption(char* inputFile, char* outputFile, int key);
    void FileDecryption(char* inputFile, char* outputFile, int key);
};
