#ifndef AUSTIN_WARD_INTERPOLATE
#define AUSTIN_WARD_INTERPOLATE

#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <tuple>

namespace cs540 {
  class WrongNumberOfArgs {};

  constexpr auto ffr (std::ostream &(*_) (std::ostream &)) { 
      return _; 
    }

  constexpr auto ffr (std::ios &(*_) (std::ios &)) { 
    return _; 
  }

  template <typename T>
  bool isManip(const T &t) {
    std::ostringstream ss{};
    ss << t;
    return ss.tellp() == 0;
  }

  template <typename ... Args>
  class Interpolate {
    private:
      std::string str_;
      std::tuple<const Args & ...> args_;

      template <size_t I>
      void finish_stream (std::ostream &o) {
        if (isManip(std::get<I> (args_)))
          o << std::get<I> (args_);
        else
          throw WrongNumberOfArgs();

        if constexpr (I + 1 < sizeof ... (Args)) {
          finish_stream<I + 1> (o);
        }
      }

      template <size_t I>
      void print (size_t idx, std::ostream &o) {
        char prev_char = '\0';
        for (; str_[idx] != '\0'; idx++) {
          if (str_[idx] == '%' && prev_char != '\\') {
            if constexpr (I < sizeof ... (Args)) {

              if (prev_char != '\0')
                o << prev_char;
              prev_char = '\0';

              o << std::get<I> (args_);
              if (!isManip(std::get<I> (args_))) // TODO: iomanipulator
                print<I + 1> (++idx, o);
              else
                print<I + 1> (idx, o);

            } else {
              throw WrongNumberOfArgs();
            }
            break;
          } else if (prev_char != '\0' && (prev_char != '\\' || str_[idx] != '%')) {
              o << prev_char;
          }
          prev_char = str_[idx];
        }

        if (prev_char != '\0')
          o << prev_char;
        else
          o << "";

        if (str_[idx] == '\0') {
          if constexpr (I + 1 < sizeof ... (Args)) {
            finish_stream<I + 1> (o);
          }
        }
      }
    public:
      Interpolate (std::string str, const Args&... args) 
        : str_(str), args_{args...} {}
  
      friend
      std::ostream &operator<< (std::ostream &o, Interpolate itp) {
        itp.print<0>(0, o);
        return o;
      }
  };
}

#endif
