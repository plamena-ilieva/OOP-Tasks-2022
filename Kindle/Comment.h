#ifndef KINDLE_COMMENT_H
#define KINDLE_COMMENT_H
#include "String.h"

class Comment {
    MyString content;
    MyString author;

public:
    Comment();
    Comment(const MyString&, const MyString&);
    void printComment() const;

    friend std::ifstream& operator<<(Comment&, std::ifstream&);
    friend std::ofstream& operator>>(const Comment&, std::ofstream &);
};
#endif //KINDLE_COMMENT_H
