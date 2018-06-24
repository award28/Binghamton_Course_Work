#ifndef AUSTIN_WARD_PRIMES
#define AUSTIN_WARD_PRIMES

#include <iostream>
#include <typeinfo>
#include <vector>
#include <math.h>       /* sqrt */


namespace cs540 {
  class Primes {
    private:
      using UL = unsigned long;
      std::vector<UL> ps;
    public:
      Primes(unsigned long top) {
        UL sq = sqrt(top);
        std::vector<bool> v;
        v.push_back(false);
        v.push_back(false);
        for (UL i = 2; i <= top; i++)
          v.push_back(true);

        for (UL i = 2; i <= sq; i++) {
          if (v.at(i)) {
            for (UL j = i*i; j <= top; j += i) {
              v.at(j) = false;
            } }
        }

        for (UL i = 0; i <= top; i++) {
          if (v.at(i)) ps.push_back(i);
        }
      }

      std::vector<UL>::iterator
        begin()
        {
          return ps.begin();
        }

      std::vector<UL>::iterator
        end() 
        {
          return ps.end();
        }
  };

}

#endif
