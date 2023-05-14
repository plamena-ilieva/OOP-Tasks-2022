#ifndef KINDLE_USER_H
#define KINDLE_USER_H

#include "Vector.hpp"
#include "String.h"
#include "Book.h"

class User {
    Vector<Book *> readBooks;
    Vector<Book *> writtenBooks;
    Vector<Book *> booksInProgress;
    Vector<unsigned short> currentPosition;
    MyString username;
    MyString password;

    bool isRead(Book *const) const;
    bool isWritten(Book *const) const;
    void throwIsValidBook(bool (*function) (Book *const), Book *const) const;

public:

    User();
    User(const MyString &, const MyString &);
    void readBook(Book *const);
    void writeBook(Book *);

    void editTitle(Book *, const MyString &);
    void addPage(Book *, const MyString &);
    void addToPage(Book *, const MyString &, size_t);
    void editPage(Book *, const MyString &, size_t);
    void insertPage(Book *, const MyString &, size_t);
    void removePage(Book *, size_t);

    void addComment(Book *, const MyString &) const;
    void readComments(Book *) const;

    void rateBook(Book *, unsigned short) const;

    bool cmpPassword(const MyString &) const;
    const MyString& getUsername() const;

    friend std::ifstream& operator<<(User&, std::ifstream&);
    friend std::ofstream& operator>>(const User&, std::ofstream &);
    //friend class Kindle;
};

#endif //KINDLE_USER_H
