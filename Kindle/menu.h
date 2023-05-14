#ifndef KINDLE_MENU_H
#define KINDLE_MENU_H
#include "Kindle.h"
long long logIn(Kindle&);
long long signUp(Kindle&);
void logOut(Kindle&, long long&);

void read(long long, Kindle&);
void write(long long, Kindle&);
void rate(long long, Kindle&);
void comment(long long, Kindle&);
void viewComments(long long, Kindle&);
void viewBooks(long long, Kindle&);

void editTitle(long long,Kindle&);
void addPage(long long, Kindle&);
void addToPage(long long, Kindle&);
void editPage(long long, Kindle&);
void insertPage(long long, Kindle&);
void removePage(long long,Kindle&);

void concat(long long, Kindle&, const MyString&, unsigned short);

void mainMenu(Kindle&, const char*);
void tryCatch(void (*function) (long long,Kindle&), long long, Kindle&);
void tryCatch(void (*function) (Kindle&, const char*), Kindle&, const char*);
void readFromFile(Kindle&, const char*);
void writeInFile(Kindle&, const char*);

#endif //KINDLE_MENU_H
