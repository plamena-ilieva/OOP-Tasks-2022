#include "menu.h"
//#include <fstream>

void mainMenu(Kindle &kindle, const char* fileName) {
    long long userIndex = -1;
    tryCatch(readFromFile, kindle, fileName);
    MyString command;
    std::cout << "Enter a command: " << std::endl;
    std::cin >> command;

    while (!(command == "quit")) {
        if (command == "login")
            userIndex = logIn(kindle);
        else if (command == "signup")
            userIndex = signUp(kindle);
        else if (command == "logout")
            logOut(kindle, userIndex);
        else if (command == "read")
            tryCatch(read, userIndex, kindle);
        else if (command == "write")
            tryCatch(write, userIndex, kindle);
        else if (command == "rate")
            tryCatch(rate, userIndex, kindle);
        else if (command == "comment")
            tryCatch(comment, userIndex, kindle);
        else if (command == "comments")
            tryCatch(viewComments, userIndex, kindle);
        else if (command == "view")
            tryCatch(viewBooks, userIndex, kindle);
        else if (command == "edit title")
            tryCatch(editTitle, userIndex, kindle);
        else if (command == "add page")
            tryCatch(addPage, userIndex, kindle);
        else if (command == "add to page")
            tryCatch(addToPage, userIndex, kindle);
        else if (command == "edit page")
            tryCatch(editPage, userIndex, kindle);
        else if (command == "insert page")
            tryCatch(insertPage, userIndex, kindle);
        else if (command == "remove page")
            tryCatch(removePage, userIndex, kindle);

        std::cout << "Enter a command: " << std::endl;
        std::cin >> command;
    }
    tryCatch(writeInFile, kindle, fileName);
}

void tryCatch(void (*function)(long long, Kindle &), long long userIndex, Kindle &kindle) {
    try {
        function(userIndex, kindle);
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void tryCatch(void (*function)(Kindle &, const char*), Kindle &kindle, const char* fileName) {
    try {
        function(kindle, fileName);
    }
    catch (char *message) {
        std::cout << message << std::endl;
    }
}

long long logIn(Kindle &kindle) {
    std::cout << "Enter username:" << std::endl;
    MyString username;
    std::cin >> username;
    std::cout << "Enter password:" << std::endl;
    MyString password;
    std::cin >> password;
    long long index = -1;
    try {
        index = kindle.logIn(username, password);
    }
    catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    std::cout << "Welcome, " << username << "!" << std::endl;
    return index;
}

long long signUp(Kindle &kindle) {
    std::cout << "Enter username:" << std::endl;
    MyString username;
    std::cin >> username;
    std::cout << "Enter password:" << std::endl;
    MyString password;
    std::cin >> password;
    long long index = -1;

    try {
        index = kindle.signUp(username, password);
    }
    catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    std::cout << "User registered!" << std::endl;
    return index;
}

void logOut(Kindle &kindle, long long &userIndex) {
    kindle.logOut();
    std::cout << "User logged out!" << std::endl;
    userIndex = -1;
}

void read(long long userIndex, Kindle &kindle) {
    MyString title;
    MyString author;
    std::cin >> title >> author;
    kindle.read(userIndex, title, author);
}

void write(long long userIndex, Kindle &kindle) {
    std::cout << "Enter title: " << std::endl;
    MyString title;
    std::cin >> title;
    try {
        kindle.write(userIndex, title);
    }
    catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return;
    }
    MyString input;
    std::cin >> input;
    kindle.addPage(userIndex, title, input);
    concat(userIndex, kindle, title, 0);
}

void rate(long long userIndex, Kindle &kindle) {
    MyString title;
    unsigned short rating;
    std::cin >> title;
    std::cin >> rating;

    kindle.rate(userIndex, title, rating);
}

void comment(long long userIndex, Kindle &kindle) {
    MyString title;
    MyString author;
    MyString content;
    std::cin >> title >> author >> content;

    kindle.comment(userIndex, title, author, content);
}

void viewComments(long long userIndex, Kindle &kindle) {
    MyString title;
    MyString author;
    std::cin >> title >> author;

    kindle.viewComments(title, author);
}

void viewBooks(long long userIndex, Kindle &kindle) {
    kindle.viewBooks();
}

void editTitle(long long userIndex, Kindle &kindle) {
    std::cout << "Enter title: " << std::endl;
    MyString title;
    std::cin >> title;
    kindle.editTitle(userIndex, title);
}

void addPage(long long userIndex, Kindle &kindle) {
    MyString title;
    std::cin >> title;
    size_t index = kindle.getSize();
    MyString input;
    std::cin >> input;
    kindle.addPage(userIndex, title, input);
    concat(userIndex, kindle, title, index);
}

void addToPage(long long userIndex, Kindle &kindle) {
    MyString title;
    std::cin >> title;
    unsigned short index;
    std::cin >> index;
    concat(userIndex, kindle, title, index);
}

void editPage(long long userIndex, Kindle &kindle) {
    MyString title;
    std::cin >> title;
    unsigned short index;
    std::cin >> index;
    MyString input;
    std::cin >> input;
    kindle.editPage(userIndex, title, input, index);
    concat(userIndex, kindle, title, index);
}

void insertPage(long long userIndex, Kindle &kindle) {
    MyString title;
    std::cin >> title;
    unsigned short index;
    std::cin >> index;
    MyString input;
    std::cin >> input;
    kindle.insertPage(userIndex, title, input, index);
    concat(userIndex, kindle, title, index);
}

void removePage(long long userIndex, Kindle &kindle) {
    MyString title;
    std::cin >> title;
    unsigned short index;
    std::cin >> index;
    kindle.removePage(userIndex, title, index);
}

void concat(long long userIndex, Kindle &kindle, const MyString &title, unsigned short index) {
    MyString input;
    std::cin >> input;
    while (!(input == ":quit")) {
        kindle.addToPage(userIndex, title, input, index);
        std::cin >> input;
    }
}

void readFromFile(Kindle &kindle, const char *fileName) {
    std::ifstream inFile(fileName, std::ios::binary);
    if (!inFile.is_open())
        throw std::invalid_argument("Error while opening file");
    kindle.readFromFile(inFile);
    try {
        inFile.close();
    }
    catch (...) {
        std::cout << "Error while closing file" << std::endl;
    }
}

void writeInFile(Kindle &kindle, const char *fileName) {
    std::ofstream outFile(fileName, std::ios::binary | std::ios::app);
    if (!outFile.is_open())
        throw std::invalid_argument("Error while opening file");
    kindle.writeInFile(outFile);
    try {
        outFile.close();
    }
    catch (...) {
        std::cout << "Error while closing file" << std::endl;
    }
}
