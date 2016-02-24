#ifndef USER_H
#define USER_H
#include <iostream>

class User {
    public:
        std::string lastName;
        std::string firstName;
        int age;
        User(std::string fname, std::string lname, int age, std::string username, std::string password) {
            this->firstName = fname;
            this->lastName = lname;
            this->age = age;
            this->username = username;
            this->password = password;
            this->favoriteMovie = new std::string[5]; 

        }
        bool authenticate(std::string password) { return (password == this->password); }
        std::string getUsername() { return this->username; }
        void setPassword(std::string new_password) { this->password = new_password; }
        std::string *movieList() { return this->favoriteMovie; }
        User(void);
    private:
        std::string *favoriteMovie;
        std::string username;
        std::string password;       
};
#endif
