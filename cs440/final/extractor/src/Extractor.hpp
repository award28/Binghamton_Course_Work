#ifndef EXTRACTOR_AUSTIN_WARD
#define EXTRACTOR_AUSTIN_WARD

#include <vector>
#include <array>
#include <iostream>
#include <any>

/* allow partial specialization */
template <size_t P, size_t ... Ps>
class Extractor;
 
template <size_t P>
class Extractor<P> {
  private:

  public:
    Extractor () {}


    template <typename T>
    constexpr std::array<T, 1> operator()(T e[]) {
      std::array<T, 1> ret_arr {e[P]};
      return ret_arr;
    }

    template <typename T, size_t S>
    constexpr std::array<T, 1> operator()(std::array<T, S> e) {
      std::array<T, 1> ret_arr {e[P]};
      return ret_arr;
    }

    template <typename T>
    constexpr std::array<T, 1> operator()(std::vector<T> e) {
      std::array<T, 1> ret_arr {e[P]};
      return ret_arr;
    }
};


template <size_t P, size_t NP, size_t ... Ps>
class Extractor<P, NP, Ps ...> {
  private:
    static const size_t n = sizeof ... (Ps);
    Extractor<NP, Ps ...> rem;

  public:
    Extractor () {}


    template <typename T>
    std::array<T, 2 + n> operator()(T elms[]) { 
      std::array<T, 2 + n> ret_arr;
      ret_arr[0] = elms[P];
      size_t i = 1;
      for (auto e : rem(elms)) {
        ret_arr[i++] = e;
      }
      return ret_arr;
    }


    template <typename T, size_t S>
    std::array<T, 2 + n> operator()(std::array<T, S> elms) { 
      std::array<T, 2 + n> ret_arr;
      ret_arr[0] = elms[P];
      size_t i = 1;
      for (auto e : rem(elms)) {
        ret_arr[i++] = e;
      }
      return ret_arr;
    }

    template <typename T>
    std::array<T, 2 + n> operator()(std::vector<T> elms) { 
      std::array<T, 2 + n> ret_arr;
      ret_arr[0] = elms[P];
      size_t i = 1;
      for (auto e : rem(elms)) {
        ret_arr[i++] = e;
      }
      return ret_arr;
    }
};

#endif
