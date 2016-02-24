#ifdef MOVIECHART_H
#define MOVIECHART_H
#include <iostream>
#include "User.h"

class MovieChart {
    private:
        User *users;
        int num_users;
        User* current_user;
    public:
        MovieChart(void);
        bool login();
        void logout(){current_user = NULL;}
        void create();
        void update();
        void view();
};
#endif


