#include "read.h"
#include "menu.h"
#include "fstream"
#include <cstring>

bool readStudentInput(std::ifstream &inFile, Student &student) {
    bool isInitName, isInitFn, isInitAge, isInitGender, isInitEmail, isInitGrade = false;
    while (true) {
        char input[MAX_SIZE];
        inFile.getline(input, MAX_SIZE);
        const char *inputPtr = input;
        while (*inputPtr != '\0') {
            while (*inputPtr == ' ' || *inputPtr == '\t') {
                ++inputPtr;
            }
            char field[MAX_FIELD_SIZE];
            if (*inputPtr == '<') {
                parseLine(field, ++inputPtr, '>');
                if (strcmp(field, "\\student") == 0) {
                    return isInitName && isInitFn && isInitAge && isInitGender &&
                           isInitEmail && isInitGrade;
                }

                char value[MAX_SIZE];
                parseLine(value, inputPtr, '<');
                inputPtr += strlen(field) + 2;

                if (strcmp(field, "name") == 0) {
                    if (!student.setName(value)) {
                        return false;
                    }
                    isInitName = true;
                } else if (strcmp(field, "fn") == 0) {
                    int fn = atoi(value);
                    student.setFN(fn);
                    isInitFn = true;

                } else if (strcmp(field, "age") == 0) {
                    int age = atoi(value);
                    if (!student.setAge(age)) {
                        return false;
                    }
                    isInitAge = true;
                } else if (strcmp(field, "gender") == 0) {
                    Gender gender;
                    if (strcmp(value, "Female") == 0) {
                        gender = Gender::female;
                    } else if (strcmp(value, "Male") == 0) {
                        gender = Gender::male;
                    } else {
                        return false;
                    }
                    student.setGender(gender);
                    isInitGender = true;
                } else if (strcmp(field, "email") == 0) {
                    if (!student.setEmail(value)) {
                        return false;
                    }
                    isInitEmail = true;
                } else if (strcmp(field, "grade") == 0) {
                    double grade = atof(value);
                    if (!student.setGrade(grade)) {
                        return false;
                    }
                    isInitGrade = true;
                }
            }
        }
    }
}

void readFromFile(StudentCollection &students, std::ifstream &inFile) {
    while (true) {
        char input[MAX_SIZE];
        inFile.getline(input, MAX_SIZE);
        const char *inputPtr = input;
        if (inFile.eof()) {
            break;
        }
        if (*inputPtr == '\0') {
            continue;
        }
        while (*inputPtr == ' ' || *inputPtr == '\t') {
            ++inputPtr;
        }
        char field[MAX_FIELD_SIZE];
        parseLine(field, inputPtr, ' ');

        if (strcmp(field, "<student>") == 0) {
            Student currentStudent;
            if (!readStudentInput(inFile, currentStudent)) {
                continue;
            }
            if (students.isUniqueStudent(currentStudent)) {
                students.addStudent(currentStudent);
            }
        }
    }
}