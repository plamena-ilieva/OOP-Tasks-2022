#include "menu.h"
const int SIZE = 1024;
int main() {
    Kindle kindle;
    char fileName[SIZE];
    std::cin.getline(fileName, SIZE);
    mainMenu(kindle, fileName);
}
