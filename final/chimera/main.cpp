#include <iostream>

// You will need to create some classes.
class Feline {
  public:
  virtual void vocalize() const {
    std::cout << "Feline noises" << std::endl;
  }
};

class Canine {
  public:
  virtual void vocalize() const {
    std::cout << "Canine noises" << std::endl;
  }
};

class Cat : public Feline {
  public:
  Cat () {}
  virtual void vocalize() const;
};

class Lion : public Feline {
  public:
  Lion () {}
  virtual void vocalize() const;
};

class Dog : public Canine {
  public:
  Dog () {}
  virtual void vocalize() const;
};

// Must not modify this function.
void
Dog::vocalize() const {
    std::cout << "Woof!" << std::endl;
}

// Must not modify this function.
void 
Cat::vocalize() const {
    std::cout << "Meow!" << std::endl;
}

// Must not change this class.
class Chimera : public Dog, public Cat {
};

void
Lion::vocalize() const {
    std::cout << "Roar!" << std::endl;
}

int
main() {

    auto cp = new Chimera;
    //cp->vocalize(); // Should give compile-time, ambiguity error.
    // Executes Dog::vocalize().
    static_cast<Canine *>(cp)->vocalize();
    // Executes Cat::vocalize().
    static_cast<Feline *>(cp)->vocalize();

    auto lp = new Lion;
    // Executes Lion::vocalize().
    static_cast<Feline *>(lp)->vocalize();
}
