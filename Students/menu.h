#ifndef HW1_2_MENU_H
#define HW1_2_MENU_H

#include "StudentCollection.h"

void parseLine(char *dest, const char *&source, char symbol);

void printMessage(bool isSuccessful);

void mainMenu(StudentCollection &students);

#endif //HW1_2_MENU_H
