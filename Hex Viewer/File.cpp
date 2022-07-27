#include "File.h"
#include <fstream>
#include <cstring>
#include "hexFunctions.h"

char File::interpret(char symbol) const {
    if (symbol >= 'a' && symbol <= 'z' ||
        symbol >= 'A' && symbol <= 'Z') {
        return symbol;
    }
    return '.';
}

void File::printByteAsHex(size_t symbol) const {
    char *hexNum = parseDecToHex(symbol);
    std::cout << (symbol <= 9 ? "0" : "") << hexNum << ' ';
    delete[] hexNum;
}

void File::printInterpretedBytes(char *arr) const {
    if (arr == nullptr) {
        return;
    }
    size_t sizeOfArr = strlen(arr);
    for (int i = 0; i < sizeOfArr; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

File::File(const char *newFilePath) {
    if (newFilePath == nullptr) {
        return;
    }

    std::ifstream inFile(newFilePath, std::ios::binary);
    if (!inFile.is_open()) {
        return;
    }
    filePath = new char[strlen(newFilePath)+1];
    strcpy(filePath, newFilePath);
    size = calcSize(inFile);
    content = new size_t[size];

    for (int i = 0; i < size; ++i) {
        char byte;
        inFile.read((char *) &byte, sizeof(byte));
        content[i] = (size_t) byte;
    }
}

File::~File() {
    delete[] content;
    delete[] filePath;
}

char *File::fileAsInterpretedBytes() const {
    char *fileBytes = new char[size];

    for (int i = 0; i < size; ++i) {
        char byte = (char) content[i];
        fileBytes[i] = interpret(byte);
    }

    fileBytes[size] = '\0';
    return fileBytes;
}

void File::view() const {
    for (int i = 0; i < size; ++i) {
        size_t byte = content[i];
        printByteAsHex(byte);
    }

    char *fileInterBytes = fileAsInterpretedBytes();
    std::cout << std::endl;
    printInterpretedBytes(fileInterBytes);
    delete[] fileInterBytes;
}

bool File::changeAtIndex(int index, char *value) {
    if (value == nullptr) {
        return false;
    }
    if (!isValidHex(value) || index >= size) {
        return false;
    }
    int hexValue = parseHexToDec(value);
    content[index] = hexValue;
    return true;
}

bool File::removeByte() {
    if (size <= 0) {
        return false;
    }
    content[--size] = 0;
    return true;
}

bool File::addByte(char *value) {
    if (value == nullptr) {
        return false;
    }
    if (!isValidHex(value)) {
        return false;
    }
    int hexValue = parseHexToDec(value);
    content[size++] = hexValue;
    return true;
}

void File::saveFile() const {
    std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
    for (int i = 0; i < size; ++i) {
        int result = content[i];
        outFile.write((const char *) &result, 1);
    }
}

void File::saveFileAs(const char *fileName) const {
    if (fileName == nullptr) {
        return;
    }
    std::ofstream outFile(fileName, std::ios::binary | std::ios::trunc);
    for (int i = 0; i < size; ++i) {
        int result = content[i];
        outFile.write((const char *) &result, 1);
    }
}

size_t calcSize(std::ifstream &inFile) {
    size_t currentPosition = inFile.tellg();
    inFile.seekg(0, std::ios::end);
    size_t result = inFile.tellg();
    inFile.seekg(currentPosition);
    return result;
}

