#ifndef HW1_MENU_H
#define HW1_MENU_H

#include "File.h"

const int SIZE = 1024;
const int COMMAND_SIZE = 10;

void parseWord(const char *&input, char dest[]);

void printMessage(bool isSuccessful);

void mainMenu(File &file);

#endif //HW1_MENU_H
