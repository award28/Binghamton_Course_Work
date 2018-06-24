#include <iostream>
 
 using namespace std;

int main() {
 map<string, Book> record;
 
 char stop = false;
 
 String isbn, title, author;
 
 int quantity;
 
 Book book;
 
 while(stop != ‘n’) {
 
 cout << “Enter this books ISBN#: “;
 
 cin >> isbn;
 
 cout << “Enter this books Title: “;
 
 cin.ignore(256, '\n');
 
 getline(cin, title);
 
 cout << “Enter this books Author: “;
 
 getline(cin, author); 
 
 cout << “Enter this books Quantity: ”;
 
 cin >> quantity;
 
 book = book(title, author, quantity);
 
 record.insert(pair<string, Book>(isbn, book));
 
 cout << “Would you like to continue? (y/n): “;
 
 cin >> stop;
 }
