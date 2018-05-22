#ifndef AUSTIN_WARD_ARRAY
#define AUSTIN_WARD_ARRAY

#include <iostream>
#include <vector>
#include <ctime>
#include <sys/time.h>
#include <assert.h>

#include "MyInt.hpp"


namespace cs540 {
  class Array {
    private:
      std::vector<MyInt> v_;
      Array(std::vector<MyInt> list) : v_(std::move(list)) {}

    public:
      Array(std::initializer_list<MyInt> list) : v_(list) {}
      Array(Array &arr) : v_(arr.v_) {}
      Array(Array &&arr) : v_(std::move(arr.v_)) {}

      Array &operator=(Array &arr) { 
        v_ = arr.v_;
        return *this;
      }

      Array &operator=(Array &&arr) { 
        v_ = std::move(arr.v_);
        return *this;
      }

      friend 
      std::ostream& operator<<(std::ostream& stream, const Array& arr) {
        auto begin = arr.v_.begin();
        auto end = --(arr.v_.end());

        for (auto it = begin; it != end; it++) stream << *it << ", ";
        stream << *end;

        return stream;
      } 

      static void move_performance_test() {
        double start_time, stop_time, copy_time, move_time;
        struct timeval start, stop;
        std::vector<MyInt> v;

        for (int i = 0; i < 1000; i++) v.push_back({i});
        Array a1{v};

        gettimeofday (&start, NULL);
        Array copy{a1};
        gettimeofday (&stop, NULL);

        start_time = ((start.tv_sec) * 1000 + start.tv_usec/1000.0);
        stop_time = ((stop.tv_sec) * 1000 + stop.tv_usec/1000.0);
        copy_time = stop_time - start_time;

        gettimeofday (&start, NULL);
        Array move = std::move(a1);
        gettimeofday (&stop, NULL);

        start_time = ((start.tv_sec) * 1000 + start.tv_usec/1000.0);
        stop_time = ((stop.tv_sec) * 1000 + stop.tv_usec/1000.0);
        move_time = stop_time - start_time;

        assert(copy_time > move_time);
      }
  };
}

#endif
