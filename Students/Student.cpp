#include <iostream>
#include "Student.h"
#include <cstring>

char *doubleToStr(double num) {
    char *result = new char[5];
    strcpy(result, "0.00");
    int intNum = int(num);
    num -= intNum;
    int tenth = int((num) / 0.1);
    (num *= 10) -= tenth;
    int hundred = int((num) / 0.1);
    result[0] = intNum + '0';

    result[2] = tenth + '0';
    result[3] = hundred + '0';
    return result;
}

Student::Student() {
    setName("Unknown");
    setFN(1);
    setAge(15);
    setGender(Gender::female);
    setEmail("unknown@");
    setGrade(2);
}

Student::Student(const char *newName, int newFN, int newAge, Gender newGender,
                 const char *newEmail, double newGrade) {
    setName(newName);
    setFN(newFN);
    setAge(newAge);
    setGender(newGender);
    setEmail(newEmail);
    setGrade(newGrade);
}

bool Student::isValidName(const char *newName) const {
    if (newName == nullptr) {
        return false;
    }
    return strlen(newName) <= MAX_NAME_SIZE;
}

bool Student::isValidAge(int newAge) const {
    return newAge >= 15 && newAge <= 65;
}

bool Student::contains(const char *text, char symbol) const {
    if (text == nullptr) {
        return false;
    }

    size_t newEmailSize = strlen(text);

    for (int i = 0; i < newEmailSize; ++i) {
        if (text[i] == symbol) {
            return true;
        }
    }
    return false;
}

bool Student::isValidEmail(const char *newEmail) const {
    if (newEmail == nullptr) {
        return false;
    }
    return isValidName(newEmail) && contains(newEmail, '@');
}

bool Student::isValidGrade(double newGrade) const {
    return !(newGrade < 2 || newGrade > 6);
}

const char *Student::getName() const {
    return name;
}

int Student::getFN() const {
    return fn;
}

int Student::getAge() const {
    return age;
}

Gender Student::getGender() const {
    return gender;
}

const char *Student::getEmail() const {
    return email;
}

double Student::getGrade() const {
    return grade;
}

bool Student::setName(const char *newName) {
    if (isValidName(newName)) {
        strcpy(name, newName);
        return true;
    }
    return false;
}

void Student::setFN(int newFN) {
    fn = newFN;
}

bool Student::setAge(int newAge) {
    if (isValidAge(newAge)) {
        age = newAge;
        return true;
    }
    return false;
}

void Student::setGender(Gender newGender) {
    gender = newGender;
}

bool Student::setEmail(const char *newEmail) {
    if (isValidEmail(newEmail)) {
        strcpy(email, newEmail);
        return true;
    }
    return false;
}

bool Student::setGrade(double newGrade) {
    if (isValidGrade(newGrade)) {
        grade = newGrade;
        return true;
    }
    return false;
}

void Student::printStudent() const {
    char *gradeAsStr = doubleToStr(grade);
    std::cout << "Name: " << name << ", FN: " << fn << ", Age: " << age
              << ", Gender: " << (gender == Gender::female ? "female" : "male")
              << ", Email: " << email << ", Grade: " << gradeAsStr << std::endl;
    delete[] gradeAsStr;
}

void Student::saveStudent(std::ofstream &outFile) const {
    char *gradeAsStr = doubleToStr(grade);
    outFile << "<student>" << std::endl
            << "\t" << "<name>" << name << "<\\name>" << std::endl
            << "\t" << "<fn>" << fn << "<\\fn>" << std::endl
            << "\t" << "<age>" << age << "<\\age>" << std::endl
            << "\t" << "<gender>" << (gender == Gender::female ? "Female" : "Male") << "<\\gender>" << std::endl
            << "\t" << "<email>" << email << "<\\email>" << std::endl
            << "\t" << "<grade>" << gradeAsStr << "<\\grade>" << std::endl
            << "<\\student>" << std::endl << std::endl;
    delete[] gradeAsStr;
}