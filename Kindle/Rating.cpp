#include "Rating.h"

Rating::Rating() {
    //author = "";
    score = 0;
}
Rating::Rating(unsigned short score, const MyString& author) {
    this->author = author;
    this->score = score;
}

unsigned short Rating::getScore() const {
    return score;
}

void Rating::setScore(unsigned short newScore) {
    score = newScore;
}

bool Rating::operator==(const Rating& other) const {
    return author == other.author;
}
void Rating::printRating() const {
    std::cout << author << " rated " << score << " stars!" << std::endl;
}

std::ifstream& operator<<(Rating& rating, std::ifstream &inFile) {
    inFile.read((char*)&rating.score, sizeof(rating.score));
    rating.author << inFile;
    return inFile;
}

std::ofstream &operator>>(const Rating& rating, std::ofstream &outFile) {
    outFile.write((const char*)&rating.score, sizeof(rating.score));
    rating.author >> outFile;
    return outFile;
}