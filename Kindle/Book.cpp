#include "Book.h"

Book::Book() {
    //title = "";
    //author = "";
    rating = 0;
}

Book::Book(const MyString &newTitle, const MyString &newAuthor) {
    title = newTitle;
    author = newAuthor;
    rating = 0;
}

void Book::printBookInfo() const {
    std::cout << title << " by " << author << std::endl;
}

void Book::editTitle(const MyString &titleStr) {
    title = titleStr;
}

void Book::addPage(const MyString &pageStr) {
    Page page(pageStr);
    pages.push_back(page);
}

void Book::addToPage(const MyString &pageStr, unsigned short index) {
    std::ofstream log("log.txt" , std::ios::app);
    log << "book" << std::endl;
    Page page(pageStr);
    pages[index].concat(page);
}

void Book::editPage(const MyString &pageStr, unsigned short index) {
    //Page page(pageStr);
    pages[index] = Page(pageStr);///
}

void Book::insertPage(const MyString &pageStr, unsigned short index) {
    Page page(pageStr);
    pages.insert(page, index);
}

void Book::removePage(unsigned short index) {
    pages.deleteAt(index);
}

const Page &Book::operator[](unsigned short index) const {
    return pages[index];
}

bool Book::operator==(const Book& other) const {
    return title == other.title;
}

unsigned int Book::getSize() const {
    return pages.getSize();
}

const MyString& Book::getTitle() const {
    return title;
}

void Book::setTitle(const MyString& newTitle) {
    title = newTitle;
}

void Book::addComment(const MyString &commentContent, const MyString &commentAuthor) {
    Comment comment(commentContent, commentAuthor);
    comments.push_back(comment);
}

void Book::printComments() const {
    for (int i = 0; i < comments.getSize(); ++i) {
        comments[i].printComment();
    }
}

void Book::addRating(unsigned short score, const MyString &author) {
    Rating newRating(score, author);
    long long index = ratings.findItem(newRating);
    if (index == -1) {
        rating = (rating + score / ratings.getSize()) * ratings.getSize() / (ratings.getSize() + 1);
        ratings.push_back(newRating);
    } else {
        (rating -= ratings[index].getScore() / ratings.getSize()) += score / ratings.getSize();
        ratings[index].setScore(score);
    }
}

void Book::printRatings() const {
    for (int i = 0; i < ratings.getSize(); ++i) {
        ratings[i].printRating();
    }
}

std::ifstream& operator<<(Book& book, std::ifstream&inFile) {
    book.title << inFile;
    book.author << inFile;
    book.pages.readFromFileObj(inFile);
    book.comments.readFromFileObj(inFile);
    book.ratings.readFromFileObj(inFile);
    inFile.read((char*)&book.rating, sizeof(book.rating));
    return inFile;
}

std::ofstream& operator>>(const Book& book, std::ofstream &outFile) {
    book.title >> outFile;
    book.author >> outFile;
    book.pages.writeInFileObj(outFile);
    book.comments.writeInFileObj(outFile);
    book.ratings.writeInFileObj(outFile);
    outFile.write((const char*)&book.rating, sizeof(book.rating));
    return outFile;
}