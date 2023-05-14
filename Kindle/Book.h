#ifndef KINDLE_BOOK_H
#define KINDLE_BOOK_H
#include "Page.h"
#include "Comment.h"
#include "Rating.h"
#include "Vector.hpp"
class Book {
    MyString title;
    MyString author;
    Vector<Page> pages;
    Vector<Comment> comments;
    Vector<Rating> ratings;
    unsigned short rating;

public:
    Book();
    Book(const MyString&, const MyString&);
    //const MyString& getTitle() const;
    //const MyString& getAuthor() const;
    void printBookInfo() const;

    void editTitle(const MyString&);
    void addPage(const MyString&);
    void addToPage(const MyString&, unsigned short);
    void editPage(const MyString&, unsigned short);
    void insertPage(const MyString&, unsigned short);
    void removePage(unsigned short);

    const Page& operator[](unsigned short) const;
    bool operator==(const Book&) const;
    unsigned int getSize() const;
    const MyString& getTitle() const;
    void setTitle(const MyString&);

    void addComment(const MyString&, const MyString&);
    void printComments() const;

    void addRating(unsigned short, const MyString&);
    void printRatings() const;

    friend std::ifstream& operator<<(Book&, std::ifstream&);
    friend std::ofstream& operator>>(const Book&, std::ofstream &);

};
#endif //KINDLE_BOOK_H
