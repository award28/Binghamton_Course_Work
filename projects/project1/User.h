#ifndef USER_H
#define USER_H
#include <iostream>
#include "LinkedList.h"
class MovieChart;

class User {
    friend class MovieChart;
    public:
        std::string lastName;
        std::string firstName;
        int age;
        User(void){}
        User(std::string fname, std::string lname, int age, std::string username, std::string password, const LinkedList<std::string> *L) {
            this->firstName = fname;
            this->lastName = lname;
            this->age = age;
            this->username = username;
            this->password = password;
            this->favoriteMovie = new LinkedList<std::string>(*L);
        }
        User(const User& other) {
            this->firstName = other.firstName;
            this->lastName = other.lastName;
            this->age = other.age;
            this->username = other.username;
            this->password = other.password;
            this->favoriteMovie = other.favoriteMovie;
        }
        ~User() {}
        bool authenticate(std::string password) {return (password == this->password);}
        std::string getUsername() {return this->username;}
        void setPassword(std::string new_password) {this->password = new_password;}
        LinkedList<std::string> movieList() {return *favoriteMovie;}
       void addMovie(std::string movie) {
            this->favoriteMovie->insert(movie);
       }
       void removeMovie(std::string movie) {
           std::string temp;
           this->favoriteMovie->reset();
           while(this->favoriteMovie->get()) {
               temp = *this->favoriteMovie->get();
               if( temp == movie)  
                   this->favoriteMovie->remove();
               this->favoriteMovie->next();
           }
       }
    private:
        LinkedList<std::string> *favoriteMovie = NULL; 
        std::string username;
        std::string password;       
};
#endif
