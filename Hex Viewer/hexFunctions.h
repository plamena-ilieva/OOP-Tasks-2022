#ifndef HW1_HEXFUNCTIONS_H
#define HW1_HEXFUNCTIONS_H

#include <iostream>

int hexSizeOfNum(size_t num);

char *parseDecToHex(size_t num);

size_t parseHexToDec(char *value);

bool isValidHexSymbol(char symbol);

bool isValidHex(char *value);

#endif //HW1_HEXFUNCTIONS_H