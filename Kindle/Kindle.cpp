#include "Kindle.h"

size_t Kindle::getSize() const {
    return books.getSize();
}

long long Kindle::findBookIndex(const MyString &title, const MyString &author) const {
    std::ofstream log("log.txt", std::ios::app);
    if (!isLoggedInUser)
        throw std::invalid_argument("User not logged in!");
    log << "find beg" << std::endl;
    long long bookIndex = getIndex(title, author);
    log << "find end" << std::endl;
    if (bookIndex == -1) {
        throw std::invalid_argument("Book does not exist!");
    }
    return bookIndex;
}

long long Kindle::getIndex(const MyString &title, const MyString &author) const {
    //Book book(title, author);
    return books.findItem(Book(title, author));
}

long long Kindle::logIn(const MyString &username, const MyString &password) {
    if (isLoggedInUser)
        throw std::invalid_argument("User already logged in!");

    for (int i = 0; i < users.getSize(); ++i) {
        if (users[i].getUsername() == username) {
            if (users[i].cmpPassword(password)) {
                isLoggedInUser = true;
                return i;
            }
            throw std::invalid_argument("Incorrect password!");
        }
    }
    throw std::invalid_argument("Incorrect username!");
}

long long Kindle::signUp(const MyString &username, const MyString &password) {
    if (isLoggedInUser)
        throw std::invalid_argument("User already logged in!");

    for (int i = 0; i < users.getSize(); ++i) {
        if (users[i].getUsername() == username) {
            throw std::invalid_argument("Username already taken!");
        }
    }
    User user(username, password);
    users.push_back(user);
    isLoggedInUser = true;
    return users.getSize() - 1;
}

void Kindle::logOut() {
    isLoggedInUser = false;
}

void Kindle::viewBooks() const {
    if (!isLoggedInUser)
        throw std::invalid_argument("User not logged in!");

    for (int i = 0; i < books.getSize(); ++i) {
        std::cout << i + 1 << ".";
        books[i].printBookInfo();
    }
}

void Kindle::read(size_t userIndex, const MyString &title, const MyString &author) {
    long long bookIndex = findBookIndex(title, author);
    users[userIndex].readBook(&books[bookIndex]);
}

void Kindle::write(size_t userIndex, const MyString &title) {
    if (!isLoggedInUser)
        throw std::invalid_argument("User not logged in!");

    long long bookIndex = getIndex(title, users[userIndex].getUsername());
    if (bookIndex != -1) {
        throw std::invalid_argument("Book already exists!");
    }

    Book book(title, users[userIndex].getUsername());
    books.push_back(book);
    users[userIndex].writeBook(&(books[books.getSize() - 1]));
}

void Kindle::editTitle(size_t userIndex, const MyString &title) {
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    users[userIndex].editTitle(&books[bookIndex], title);
}

void Kindle::addPage(size_t userIndex, const MyString &title, const MyString &content) {
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    users[userIndex].addPage(&books[bookIndex], content);
}

void Kindle::addToPage(size_t userIndex, const MyString &title, const MyString &content, unsigned short pageIndex) {
    std::ofstream log("log.txt", std::ios::app);
    log << "kindle beg" << std::endl;
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    log << "kindle mid" << std::endl;
    users[userIndex].addToPage(&books[bookIndex], content, pageIndex);
}

void Kindle::editPage(size_t userIndex, const MyString &title, const MyString &content, unsigned short pageIndex) {
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    users[userIndex].editPage(&books[bookIndex], content, pageIndex);
}

void Kindle::insertPage(size_t userIndex, const MyString &title, const MyString &content, unsigned short pageIndex) {
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    users[userIndex].insertPage(&books[bookIndex], content, pageIndex);
}

void Kindle::removePage(size_t userIndex, const MyString &title, unsigned short pageIndex) {
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    users[userIndex].removePage(&books[bookIndex], pageIndex);
}

void Kindle::rate(size_t userIndex, const MyString &title, unsigned short score) {
    long long bookIndex = findBookIndex(title, users[userIndex].getUsername());
    users[userIndex].rateBook(&books[bookIndex], score);
}

void Kindle::comment(size_t userIndex, const MyString &title, const MyString &author, const MyString &content) {
    long long bookIndex = findBookIndex(title, author);
    users[userIndex].addComment(&books[bookIndex], content);
}

void Kindle::viewRatings(const MyString &title, const MyString &author) const {
    long long bookIndex = findBookIndex(title, author);
    books[bookIndex].printRatings();
}

void Kindle::viewComments(const MyString &title, const MyString &author) const {
    long long bookIndex = findBookIndex(title, author);
    books[bookIndex].printComments();
}

void Kindle::readFromFile(std::ifstream &inFile) {
    books.readFromFileObj(inFile);
    users.readFromFileObj(inFile);
    readUsersFromFile(inFile);
    isLoggedInUser = false;
}

void Kindle::writeInFile(std::ofstream &outFile) {
    books.writeInFileObj(outFile);
    users.writeInFileObj(outFile);
    writeUsersInFile(outFile);
    isLoggedInUser = false;
}

void Kindle::readUsersFromFile(std::ifstream &inFile) {
    //read size of titles
    //read titles, find their address in the kindle, add the pointers
}

void Kindle::writeUsersInFile(std::ofstream &outFile) {
    //save titles of books
}