#ifndef USER_H
#define USER_H
#include <iostream>

class User {
    public:
        std::string lastName;
        std::string firstName;
        int age;
        User(std::string fname, std::string lname, int age, std::string username, std::string password);
        bool authenticate(std::string password);
        std::string getUsername();
        void setPassword(std::string new_password);
        std::string *movieList();
        std::string *favoriteMovie;
        User(void){ favoriteMovie = new std::string[5]; }
private:
        std::string username;
        std::string password;

        
};
void create(User &user);
void update(User &user);
void view(User &user);
void favorites(User &user);
#endif
