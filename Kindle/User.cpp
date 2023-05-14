#include "User.h"
#include "String.h"
#include <exception>
#include <iostream>

User::User() {
    //username = "";
    //password = "";
}
User::User(const MyString &newUsername, const MyString &newPassword) {
    username = newUsername;
    password = newPassword;
}

bool User::isRead(Book* const bookPtr) const {
    return readBooks.findItem(bookPtr) != -1;
}

bool User::isWritten(Book* const bookPtr) const {
    return writtenBooks.findItem(bookPtr) != -1;
}

void User::throwIsValidBook(bool (*function) (Book *const), Book *const bookPtr) const {
    if (!function(bookPtr))
        throw std::invalid_argument("Invalid book!");
}

void User::readBook(Book* const bookPtr) {
    unsigned short currentPage = 0;
    long long index = booksInProgress.findItem(bookPtr);
    if (index == -1) {
        currentPosition.push_back(currentPage);
        booksInProgress.push_back(bookPtr);
    }
    else
        currentPage = currentPosition[index];
    (*bookPtr)[currentPage].printPage();

    while (true) {
        char command;
        std::cin >> command;

        switch (command) {
            case 'n':
                (*bookPtr)[++currentPosition[index]].printPage();
                if (currentPosition[index] == (*bookPtr).getSize())
                    readBooks.push_back(bookPtr);
                break;
            case 'p':
                (*bookPtr)[--currentPosition[index]].printPage();
            case 'q':
                return;
            default:
                break;
        }
    }
}

void User::writeBook(Book* bookPtr) {
    writtenBooks.push_back(bookPtr);
}

void User::editTitle(Book* bookPtr, const MyString& str) {
    if (!isWritten(bookPtr))
        throw std::exception();

    (*bookPtr).editTitle(str);
}
void User::addPage(Book *bookPtr, const MyString &str) {
    if (!isWritten(bookPtr))
        throw std::invalid_argument("Cannot edit book!");

    (*bookPtr).addPage(str);
}

void User::addToPage(Book *bookPtr, const MyString &str, size_t index) {
    std::ofstream log("log.txt" , std::ios::app);
    log << "user" << std::endl;
    if (!isWritten(bookPtr))
        throw std::exception();

    (*bookPtr).addToPage(str, index);
}

void User::editPage(Book *bookPtr, const MyString &str, size_t index) {
    if (!isWritten(bookPtr))
        throw std::exception();

    (*bookPtr).editPage(str, index);
}

void User::insertPage(Book *bookPtr, const MyString &str, size_t index) {
    if (!isWritten(bookPtr))
        throw std::exception();

    (*bookPtr).insertPage(str, index);
}

void User::removePage(Book *bookPtr, size_t index) {
    if (!isWritten(bookPtr))
        throw std::exception();

    (*bookPtr).removePage(index);
}

void User::addComment(Book *bookPtr, const MyString &str) const {
    if (!isRead(bookPtr))
        throw std::exception();
    //throwIsValidBook(isRead(), bookPtr);
    (*bookPtr).addComment(str, username);
}

void User::readComments(Book *book) const {
    (*book).printComments();
}

void User::rateBook(Book *bookPtr, unsigned short score) const {
    if (!isRead(bookPtr))
        throw std::exception();

    (*bookPtr).addRating(score, username);
}

bool User::cmpPassword(const MyString &inputPsw) const{
    return password == inputPsw;
}

const MyString& User::getUsername() const {
    return username;
}

std::ifstream& operator<<(User& user, std::ifstream&inFile) {
    user.username << inFile;
    user.password << inFile;

    //size_t readBooksSize = user.readBooks.getSize();
    //inFile.read((char*)&readBooksSize, sizeof(readBooksSize));
    size_t readBooksCapacity = 0;
    inFile.read((char*)&readBooksCapacity, sizeof(readBooksCapacity));
    user.readBooks.setCapacity(readBooksCapacity);

    //size_t writtenBooksSize = user.writtenBooks.getSize();
    //inFile.read((char*)&writtenBooksSize, sizeof(writtenBooksSize));
    size_t writtenBooksCapacity = 0;
    inFile.read((char*)&writtenBooksCapacity, sizeof(writtenBooksCapacity));
    user.writtenBooks.setCapacity(writtenBooksCapacity);

    //size_t booksInProgressSize = user.booksInProgress.getSize();
    //inFile.read((char*)&booksInProgressSize, sizeof(booksInProgressSize));
    size_t booksInProgressCapacity = 0;
    inFile.read((char*)&booksInProgressCapacity, sizeof(booksInProgressCapacity));
    user.booksInProgress.setCapacity(booksInProgressCapacity);

    //size_t currentPositionSize = user.currentPosition.getSize();
    //inFile.read((char*)&currentPositionSize, sizeof(currentPositionSize));
    size_t currentPositionCapacity = 0;
    inFile.read((char*)&currentPositionCapacity, sizeof(currentPositionCapacity));
    user.currentPosition.setCapacity(currentPositionCapacity);

    return inFile;
}

std::ofstream& operator>>(const User& user, std::ofstream &outFile) {
    user.username >> outFile;
    user.password >> outFile;
    size_t readBooksSize = user.readBooks.getSize();
    outFile.write((const char*)&readBooksSize, sizeof(readBooksSize));
    size_t readBooksCapacity = user.readBooks.getCapacity();
    outFile.write((char*)&readBooksCapacity, sizeof(readBooksCapacity));

    size_t writtenBooksSize = user.writtenBooks.getSize();
    outFile.write((const char*)&writtenBooksSize, sizeof(writtenBooksSize));
    size_t writtenBooksCapacity = user.writtenBooks.getCapacity();
    outFile.write((const char*)&writtenBooksCapacity, sizeof(writtenBooksCapacity));

    size_t booksInProgressSize = user.booksInProgress.getSize();
    outFile.write((const char*)&booksInProgressSize, sizeof(booksInProgressSize));
    size_t booksInProgressCapacity = user.booksInProgress.getCapacity();
    outFile.write((const char*)&booksInProgressCapacity, sizeof(booksInProgressCapacity));

    size_t currentPositionSize = user.currentPosition.getSize();
    outFile.write((const char*)&currentPositionSize, sizeof(currentPositionSize));
    size_t currentPositionCapacity = user.currentPosition.getCapacity();
    outFile.write((const char*)&currentPositionCapacity, sizeof(currentPositionCapacity));

    return outFile;
}