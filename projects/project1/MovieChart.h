#ifndef MOVIECHART_H
#define MOVIECHART_H
#include <iostream>
#include "User.h"
#include "LinkedList.h"

class MovieChart {
    private:
        LinkedList<User> *users = new LinkedList<User>();
        User* current_user = NULL;
    public:
        MovieChart(void); 
        ~MovieChart(void);
        bool login();
        void logout(){current_user = NULL;}
        void create();
        void update();
        void view();
        void close();
        void list();
};
#endif


