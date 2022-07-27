#include "menu.h"
#include "File.h"
#include <iostream>
#include <cstring>

void parseWord(const char *&input, char dest[]) {
    while (*input != ' ' && *input != '\0') {
        *dest = *input;
        ++dest;
        ++input;
    }
    ++input;
    *dest = '\0';
}

void printMessage(bool isSuccessful) {
    if (!isSuccessful) {
        std::cout << "Error! Invalid data!" << std::endl;
    } else {
        std::cout << "Operation successfully executed!" << std::endl;
    }
}

void mainMenu(File &file) {
    while (true) {
        char input[SIZE];
        std::cin.getline(input, SIZE);
        char command[COMMAND_SIZE];
        const char *inputPtr = input;
        parseWord(inputPtr, command);

        if (strcmp(command, "view") == 0) {
            file.view();
        } else if (strcmp(command, "change") == 0) {
            char indexAsStr[COMMAND_SIZE];
            char value[COMMAND_SIZE];
            parseWord(inputPtr, indexAsStr);
            parseWord(inputPtr, value);
            int index = atoi(indexAsStr);
            printMessage(file.changeAtIndex(index, value));

        } else if (strcmp(command, "remove") == 0) {
            printMessage(file.removeByte());
        } else if (strcmp(command, "add") == 0) {
            char value[COMMAND_SIZE];
            parseWord(inputPtr, value);
            printMessage(file.addByte(value));
        } else if (strcmp(command, "save") == 0) {
            if (*(inputPtr - 1) == '\0') {
                file.saveFile();
                std::cout << "File successfully saved!" << std::endl;
                break;
            }

            char commandAddition[COMMAND_SIZE];
            parseWord(inputPtr, commandAddition);
            if (strcmp(commandAddition, "as") == 0) {
                char fileNewPath[COMMAND_SIZE];
                parseWord(inputPtr, fileNewPath);
                file.saveFileAs(fileNewPath);
                std::cout << "File successfully saved!" << std::endl;
                break;
            }
        } else {
            std::cout << "Incorrect command!" << std::endl;
        }
    }
}