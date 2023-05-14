#ifndef KINDLE_KINDLE_H
#define KINDLE_KINDLE_H
#include "Vector.hpp"
#include "Book.h"
#include "User.h"

class Kindle {
    Vector<Book> books;
    Vector<User> users;
    bool isLoggedInUser = false;

    long long getIndex(const MyString&, const MyString&) const;
    long long findBookIndex(const MyString&, const MyString&) const;

public:
    size_t getSize() const;
    long long logIn(const MyString&, const MyString&);
    long long signUp(const MyString&, const MyString&);
    void logOut();

    void read(size_t, const MyString&, const MyString&);
    void write(size_t, const MyString&);
    void editTitle(size_t,const MyString&);
    void addPage(size_t, const MyString&,const MyString&);
    void addToPage(size_t, const MyString&, const MyString&, unsigned short);
    void editPage(size_t, const MyString&, const MyString&, unsigned short);
    void insertPage(size_t, const MyString&,const MyString&, unsigned short);
    void removePage(size_t,const MyString&, unsigned short);
    void rate(size_t, const MyString&, unsigned short);
    void comment(size_t, const MyString&, const MyString&, const MyString&);

    void viewBooks() const;
    void viewRatings(const MyString&, const MyString&) const;
    void viewComments(const MyString&, const MyString&) const;

    void readFromFile(std::ifstream&);
    void writeInFile(std::ofstream &);

    void readUsersFromFile(std::ifstream&);
    void writeUsersInFile(std::ofstream &);
};
#endif //KINDLE_KINDLE_H
