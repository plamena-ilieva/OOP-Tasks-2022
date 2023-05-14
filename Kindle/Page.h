#ifndef KINDLE_PAGE_H
#define KINDLE_PAGE_H
#include "String.h"
#include "Vector.hpp"

class Page {
    MyString content;

public:
    Page();
    explicit Page(const MyString&);
    void concat(const Page&);
    void printPage() const;
    friend std::ifstream& operator<<(Page&, std::ifstream&);
    friend std::ofstream& operator>>(const Page&, std::ofstream &);
};

#endif //KINDLE_PAGE_H
