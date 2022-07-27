#include <iostream>
#include <fstream>
#include "menu.h"

int main() {

    long x = 25409;
    std::ofstream fileInput("myData.txt", std::ios::binary | std::ios::trunc);
    fileInput.write((const char *) &x, sizeof(x));
    fileInput.close();

    std::cout << "Enter a file path:" << std::endl;
    char filePath[SIZE];
    std::cin.getline(filePath, SIZE);
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cout << "Error while opening file!" << std::endl;
        return -1;
    }

    File file(filePath);
    std::cout << "File loaded successfully! Size: " << file.size << " bytes" << std::endl;
    mainMenu(file);
    return 0;
}