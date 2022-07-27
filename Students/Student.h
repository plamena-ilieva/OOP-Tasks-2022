#ifndef HW1_2_STUDENT_H
#define HW1_2_STUDENT_H
#include "Gender.h"
#include <fstream>
const int MAX_NAME_SIZE = 25;
const int MAX_SIZE = 256;
const int MAX_FIELD_SIZE = 10;
char* doubleToStr(double num);

class Student {
    char name[MAX_NAME_SIZE];
    char email[MAX_NAME_SIZE];
    double grade;
    int fn;
    int age;
    Gender gender;

    bool contains(const char *text, char symbol) const;

    bool isValidAge(int newAge) const;

    bool isValidName(const char *newName) const;

    bool isValidEmail(const char *newEmail) const;

    bool isValidGrade(double newGrade) const;

public:
    Student();

    Student(const char *newName, int newFN, int newAge, Gender newGender,
            const char *newEmail, double newGrade);

    const char *getName() const;

    int getFN() const;

    int getAge() const;

    Gender getGender() const;

    const char *getEmail() const;

    double getGrade() const;

    bool setName(const char *newName);

    void setFN(int newFN);

    bool setAge(int newAge);

    void setGender(Gender newGender);

    bool setEmail(const char *newEmail);

    bool setGrade(double newGrade);

    void printStudent() const;

    void saveStudent(std::ofstream &outFile) const;
};

#endif //HW1_2_STUDENT_H