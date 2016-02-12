#ifndef DOG_H
#define DOG_H
#include <string>

class Dog {
        private:
            static int id;
            int unique_id;
            String breed;
        public:
            String name;
            Dog(String name);
            void setBreed(String newBreed);
            String getBreed(void);
            void adopted(void);
};
#endif
