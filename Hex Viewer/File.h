#ifndef HW1_FILE_H
#define HW1_FILE_H

#include <iostream>

struct File {
    size_t *content;
    char *filePath;
    size_t size;

    File(const char *newFilePath);
    File(const File& other) = delete;
    File& operator=(const File& other) = delete;
    ~File();

    void view() const;
    bool changeAtIndex(int index, char *value);
    bool removeByte();
    bool addByte(char *value);
    void saveFile() const;
    void saveFileAs(const char *fileName) const;

private:
    char interpret(char symbol) const;
    void printByteAsHex(size_t symbol) const;
    void printInterpretedBytes(char *arr) const;
    char *fileAsInterpretedBytes() const;
};

size_t calcSize(std::ifstream &inFile);

#endif //HW1_FILE_H