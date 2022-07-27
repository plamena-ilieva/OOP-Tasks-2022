#include "menu.h"
#include <cstring>

void parseLine(char *dest, const char *&source, char symbol) {
    while (*source != symbol && *source != '\0') {
        *dest = *source;
        ++dest;
        ++source;
    }
    ++source;
    *dest = '\0';
}

bool edit(StudentCollection &studentCollection, const char *input) {
    if (input == nullptr) {
        return false;
    }
    char fnAsStr[MAX_NAME_SIZE];
    char field[MAX_FIELD_SIZE];
    char value[MAX_SIZE];
    parseLine(fnAsStr, input, ' ');
    parseLine(field, input, ' ');
    parseLine(value, input, ' ');
    int fn = atoi(fnAsStr);

    if (strcmp(field, "name") == 0) {
        return studentCollection.changeStudentName(fn, value);
    } else if (strcmp(field, "fn") == 0) {
        int intValue = atoi(value);
        return studentCollection.changeStudentFn(fn, intValue);
    } else if (strcmp(field, "age") == 0) {
        int intValue = atoi(value);
        return studentCollection.changeStudentAge(fn, intValue);
    } else if (strcmp(field, "gender") == 0) {
        Gender gender;
        if (strcmp(value, "female") == 0) {
            gender = Gender::female;
        } else if (strcmp(value, "male") == 0) {
            gender = Gender::male;
        } else {
            return false;
        }
        return studentCollection.changeStudentGender(fn, gender);
    } else if (strcmp(field, "email") == 0) {
        return studentCollection.changeStudentEmail(fn, value);
    } else if (strcmp(field, "grade") == 0) {
        double doubleValue = atof(value);
        return studentCollection.changeStudentGrade(fn, doubleValue);
    }
    return false;
}

bool sort(StudentCollection &studentCollection, const char *input) {
    if (input == nullptr) {
        return false;
    }
    char field[MAX_FIELD_SIZE];
    parseLine(field, input, ' ');
    return studentCollection.sortStudentCollection(field);
}

void printMessage(bool isSuccessful) {
    if (!isSuccessful) {
        std::cout << "Error! Invalid data!" << std::endl;
    } else {
        std::cout << "Operation successfully executed!" << std::endl;
    }
}

void mainMenu(StudentCollection &students) {
    while (true) {
        char input[MAX_SIZE];
        std::cin.getline(input, MAX_SIZE);
        const char *inputPtr = input;
        char command[MAX_FIELD_SIZE];
        parseLine(command, inputPtr, ' ');

        if (strcmp(command, "edit") == 0) {
            printMessage(edit(students, inputPtr));
        } else if (strcmp(command, "sort") == 0) {
            printMessage(sort(students, inputPtr));
        } else if (strcmp(command, "print") == 0) {
            students.printStudentCollection();
        } else if (strcmp(command, "save") == 0) {
            students.saveStudentCollection();
            break;
        } else {
            std::cout << "Error! Incorrect command!" << std::endl;
        }
    }
}