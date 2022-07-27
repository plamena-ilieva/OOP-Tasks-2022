#include "hexFunctions.h"
#include <cstring>

bool isValidHexSymbol(char symbol) {
    return (symbol >= '0' && symbol <= '9') ||
           (symbol >= 'a' && symbol <= 'f') ||
           (symbol >= 'A' && symbol <= 'F');
}

bool isValidHex(char *value) {
    if (value == nullptr) {
        return false;
    }
    int size = strlen(value);
    for (int i = 0; i < size; ++i) {
        if (!isValidHexSymbol(value[i])) {
            return false;
        }
    }
    return true;
}

int hexSizeOfNum(size_t num) {
    int counter = 1;
    while (num > 16) {
        num /= 16;
        ++counter;
    }
    return counter;
}

char *parseDecToHex(size_t num) {
    int size = hexSizeOfNum(num);
    char *result = new char[size + 1];

    for (int i = size - 1; i >= 0; --i) {
        int symbol = num % 16;
        if (symbol <= 9) {
            result[i] = symbol + '0';
        } else {
            result[i] = symbol + 55;
        }
        num /= 16;
    }
    result[size] = '\0';
    return result;
}

size_t parseHexToDec(char *value) {
    if (value == nullptr) {
        return 0;
    }
    int size = strlen(value);
    int counter = 1;
    size_t result = 0;

    for (int i = size - 1; i >= 0; --i) {
        char symbol = value[i];
        if (symbol >= 'A' && symbol <= 'F' ||
            symbol >= 'a' && symbol <= 'f') {
            result += (symbol - 55) * counter;
        } else if (symbol >= '0' && symbol <= '9') {
            result += (symbol - '0') * counter;
        }
        counter *= 16;
    }
    return result;
}