#ifndef KINDLE_RATING_H
#define KINDLE_RATING_H
#include "String.h"

class Rating {
    MyString author;
    unsigned short score;

public:
    Rating();
    Rating(unsigned short, const MyString&);

    unsigned short getScore() const;
    void setScore(unsigned short);

    bool operator==(const Rating&) const;
    void printRating() const;

    friend std::ifstream& operator<<(Rating&, std::ifstream&);
    friend std::ofstream& operator>>(const Rating&, std::ofstream &);
};

#endif //KINDLE_RATING_H
