#ifndef MOVIECHART_H
#define MOVIECHART_H
#include <iostream>
#include "User.h"

class MovieChart {
    private:
        User *users[255];
        int num_users;
        User* current_user;
    public:
        MovieChart(void) { 
            num_users = 0;
            current_user = NULL;
        }
        bool login();
        void logout(){current_user = NULL;}
        void create();
        void update();
        void view();
};
#endif


