#include "Page.h"

Page::Page() {

}

Page::Page(const MyString &str) {
    content = str;
}

void Page::concat(const Page &page) {
    content += page.content;
}

void Page::printPage() const {
    std::cout << content;
}

std::ifstream& operator<<(Page& page, std::ifstream &inFile) {
    page.content << inFile;
    return inFile;
}

std::ofstream &operator>>(const Page& page, std::ofstream &outFile) {
    page.content >> outFile;
    return outFile;
}