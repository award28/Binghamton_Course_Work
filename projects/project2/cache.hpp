#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

typedef std::pair<bool, unsigned int> memInstruction;
typedef std::pair<unsigned int, unsigned int> addr;

class DMapped {
 public:
  DMapped(const std::vector<memInstruction>& trace);
  void execute(unsigned int size);
  unsigned int numHits;
  unsigned int numMisses;

 private:
  std::vector<unsigned int> cache;
  std::vector<memInstruction> trace;
  unsigned int size;
  unsigned int capacity;
};

class Row {
 public:
  Row(unsigned int size) {
      this->capacity = size;
      this->counter = 0;
      this->cache.resize(this->capacity);

      std::fill(this->cache.begin(), this->cache.end() + this->capacity, std::make_pair(0, 0));
  }
  bool inCache(unsigned int, bool);

 private:
  bool compare(const addr &i, const addr &j);
  unsigned int counter;
  unsigned int capacity;
  std::vector<addr> cache;
};

#endif
