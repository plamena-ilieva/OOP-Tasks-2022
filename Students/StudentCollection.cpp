#include "StudentCollection.h"
#include <iostream>
#include <cstring>

StudentCollection::StudentCollection(const char *newFilePath) {
    size = 0;
    setFileName(newFilePath);
}

void StudentCollection::setFileName(const char *newFilePath) {
    if (newFilePath == nullptr) {
        strcpy(filePath, "unknown");
        return;
    }
    strcpy(filePath, newFilePath);
}

void StudentCollection::addStudent(const Student &student) {
    studentCollection[size++] = student;
}

int StudentCollection::findStudentIndex(int fn) const {
    for (int i = 0; i < size; ++i) {
        if (studentCollection[i].getFN() == fn) {
            return i;
        }
    }
    return -1;
}

bool StudentCollection::changeStudentName(int fn, const char *newName) {
    int index = findStudentIndex(fn);
    if (index == -1) {
        return false;
    }
    return studentCollection[index].setName(newName);
}

bool StudentCollection::changeStudentFn(int fn, int newValue) {
    int index = findStudentIndex(fn);
    if (index == -1) {
        return false;
    }
    studentCollection[index].setFN(newValue);
    return true;
}

bool StudentCollection::changeStudentAge(int fn, int newValue) {
    int index = findStudentIndex(fn);
    if (index == -1) {
        return false;
    }
    return studentCollection[index].setAge(newValue);
}

bool StudentCollection::changeStudentGender(int fn, Gender newValue) {
    int index = findStudentIndex(fn);
    if (index == -1) {
        return false;
    }
    studentCollection[index].setGender(newValue);
    return true;
}

bool StudentCollection::changeStudentEmail(int fn, const char *newEmail) {
    int index = findStudentIndex(fn);
    if (index == -1) {
        return false;
    }
    return studentCollection[index].setEmail(newEmail);

}

bool StudentCollection::changeStudentGrade(int fn, double newValue) {
    int index = findStudentIndex(fn);
    if (index == -1) {
        return false;
    }
    return studentCollection[index].setGrade(newValue);
}

bool StudentCollection::sortStudentCollection(const char *field) {
    if (strcmp(field, "name") == 0) {
        sortByName();
    } else if (strcmp(field, "fn") == 0) {
        sortByFN();
    } else if (strcmp(field, "age") == 0) {
        sortByAge();
    } else if (strcmp(field, "gender") == 0) {
        sortByGender();
    } else if (strcmp(field, "email") == 0) {
        sortByEmail();
    } else if (strcmp(field, "grade") == 0) {
        sortByGrade();
    } else {
        return false;
    }
    return true;
}

void StudentCollection::printStudentCollection() const {
    for (int i = 0; i < size; ++i) {
        studentCollection[i].printStudent();
    }
}

void StudentCollection::saveStudentCollection() const {
    std::ofstream outFile(filePath, std::ios::trunc);
    for (int i = 0; i < size; ++i) {
        studentCollection[i].saveStudent(outFile);
    }
    outFile.close();
}

bool StudentCollection::isUniqueStudent(const Student &student) const {
    int result = findStudentIndex(student.getFN());
    return result == -1;
}

void StudentCollection::swap(Student &student1, Student &student2) {
    Student temp = student1;
    student1 = student2;
    student2 = temp;
}

void StudentCollection::sortByName() {
    char minName[25];
    int index = 0;

    for (int i = 0; i < size - 1; ++i) {
        strcpy(minName, studentCollection[i].getName());
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(studentCollection[j].getName(), minName) < 0) {
                strcpy(minName, studentCollection[j].getName());
                index = j;
            }
        }
        swap(studentCollection[i], studentCollection[index]);
    }
}

void StudentCollection::sortByEmail() {
    char minEmail[25];
    int index = 0;

    for (int i = 0; i < size - 1; ++i) {
        strcpy(minEmail, studentCollection[i].getEmail());
        for (int j = i + 1; j < size; ++j) {
            if (strcmp(studentCollection[j].getEmail(), minEmail) < 0) {
                strcpy(minEmail, studentCollection[j].getEmail());
                index = j;
            }
        }
        swap(studentCollection[i], studentCollection[index]);
    }
}

void StudentCollection::sortByFN() {
    int index = 0;

    for (int i = 0; i < size - 1; ++i) {
        int minFN = studentCollection[i].getFN();
        for (int j = i + 1; j < size; ++j) {
            int currentFN = studentCollection[j].getFN();
            if (currentFN < minFN) {
                minFN = currentFN;
                index = j;
            }
        }
        swap(studentCollection[i], studentCollection[index]);
    }
}

void StudentCollection::sortByAge() {
    int index = 0;

    for (int i = 0; i < size - 1; ++i) {
        int minAge = studentCollection[i].getAge();
        for (int j = i + 1; j < size; ++j) {
            int currentAge = studentCollection[j].getAge();
            if (currentAge < minAge) {
                minAge = currentAge;
                index = j;
            }
        }
        swap(studentCollection[i], studentCollection[index]);
    }
}

void StudentCollection::sortByGender() {
    int femaleCount = getFemaleCount();

    for (int i = 0; i < femaleCount; ++i) {
        if (studentCollection[i].getGender() == Gender::female) {
            continue;
        }
        for (int j = i + 1; j < size; ++j) {
            if (studentCollection[j].getGender() == Gender::female) {
                swap(studentCollection[i], studentCollection[j]);
                break;
            }
        }
    }
}

void StudentCollection::sortByGrade() {
    int index = 0;

    for (int i = 0; i < size; ++i) {
        double maxGrade = studentCollection[i].getGrade();
        for (int j = i + 1; j < size; ++j) {
            double currentGrade = studentCollection[j].getGrade();
            if (currentGrade > maxGrade) {
                maxGrade = currentGrade;
                index = j;
            }
        }
        swap(studentCollection[i], studentCollection[index]);
    }
}

int StudentCollection::getFemaleCount() const {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (studentCollection[i].getGender() == Gender::female) {
            ++count;
        }
    }
    return count;
}