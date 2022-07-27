#include <iostream>
#include "Student.h"
#include "StudentCollection.h"
#include "menu.h"
#include "read.h"

int main() {
    std::cout << "Enter a file path:" << std::endl;
    char filePath[MAX_SIZE];
    std::cin.getline(filePath, MAX_SIZE);
    std::ifstream inFile(filePath);

    if (!inFile.is_open()) {
        std::cout << "Error while opening file!" << std::endl;
        return -1;
    }
    std::cout << "File loaded successfully!" << std::endl;
    StudentCollection students(filePath);

    readFromFile(students, inFile);
    mainMenu(students);
    return 0;
}