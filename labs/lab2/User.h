#ifndef USER_H
#define USER_H
#include <iostream>

class User {
    public:
        std::string lastName;
        std::string firstName;
        int age;
        std::string *favoriteMovie;
        User(void){ favoriteMovie = new std::string[5]; }
};
void create(User &user);
void update(User &user);
void view(User &user);
void favorites(User &user);
#endif
