#ifndef HW1_2_STUDENTCOLLECTION_H
#define HW1_2_STUDENTCOLLECTION_H

#include "Student.h"
#include <iostream>

struct StudentCollection {
    Student studentCollection[MAX_SIZE];
    size_t size;
    char filePath[MAX_SIZE];

    StudentCollection(const char *newFilePath);

    void setFileName(const char *newFilePath);

    void addStudent(const Student &student);

    bool changeStudentName(int fn, const char *newName);

    bool changeStudentFn(int fn, int newFn);

    bool changeStudentAge(int fn, int newAge);

    bool changeStudentGender(int fn, Gender newGender);

    bool changeStudentEmail(int fn, const char *newEmail);

    bool changeStudentGrade(int fn, double newGrade);

    bool sortStudentCollection(const char *field);

    void printStudentCollection() const;

    void saveStudentCollection() const;

    bool isUniqueStudent(const Student &student) const;


private:
    void swap(Student &student1, Student &student2);

    int findStudentIndex(int fn) const;

    void sortByName();

    void sortByFN();

    void sortByAge();

    void sortByGender();

    void sortByEmail();

    void sortByGrade();

    int getFemaleCount() const;

};

#endif //HW1_2_STUDENTCOLLECTION_H