#include "Comment.h"

Comment::Comment() {
    //content = "";
    //author = "";
}

Comment::Comment(const MyString &content, const MyString &author) {
    this->content = content;
    this->author = author;
}

void Comment::printComment() const {
    std::cout << author << " wrote: " << content << std::endl;
}

std::ifstream &operator<<(Comment &comment, std::ifstream &inFile) {
    comment.content << inFile;
    comment.author << inFile;
    return inFile;
}

std::ofstream &operator>>(const Comment &comment, std::ofstream &outFile) {
    comment.content >> outFile;
    comment.author >> outFile;
    return outFile;
}