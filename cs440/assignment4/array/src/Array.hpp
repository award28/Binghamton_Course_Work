#include <iostream>
#include <vector>
#include <typeinfo>
#include <cassert>
#include <typeinfo>

namespace cs540 {
  /* exception(s) */
  class OutOfRange {};

  /* allow partial specialization */
  template <typename T, size_t ... Dims>
  class Array;
  
  /* base case */
  template <typename T, size_t N>
  class Array<T, N> {

    /* friend(s) */
    template <typename U, size_t ... Dims>
    friend class Array;


    private:
      std::vector<T> v = std::vector<T>(N);


    public:
      using ValueType = T;
      class FirstDimensionMajorIterator;
      FirstDimensionMajorIterator iter;


      Array () = default;


      Array (const Array &arr) {
        for (size_t i = 0; i < N; i++)
          v.at(i) = arr.v.at(i); 
      }


      Array &operator= (const Array &arr) {
        for (size_t i = 0; i < N; i++)
          v.at(i) = arr.v.at(i);
        return *this;
      }


      template <typename U>
      Array (const Array<U, N> &arr) {
        for (size_t i = 0; i < N; i++)
          v.at(i) = arr.v.at(i);
      }


      template <typename U>
      Array &operator= (const Array<U, N> &arr) {
        for (size_t i = 0; i < N; i++)
          v.at(i) = arr.v.at(i);
        return *this;
      }


      T &operator[](size_t n) {
        try {
          return v.at(n);
        } catch (std::out_of_range) {
          throw OutOfRange();
        }
      }


      const T &operator[](size_t n) const {
        try {
          return v.at(n);
        } catch (std::out_of_range) {
          throw OutOfRange();
        }
      }


      FirstDimensionMajorIterator fmbegin() {
        return FirstDimensionMajorIterator(v, v.begin());
        
      }


      FirstDimensionMajorIterator fmend() {
        return FirstDimensionMajorIterator(v, v.end());
      }

     
      class FirstDimensionMajorIterator {
        public:
          std::vector<T> v_;
          typename std::vector<T>::iterator it_;


          FirstDimensionMajorIterator() {}


          FirstDimensionMajorIterator(std::vector<T> &v, 
              typename std::vector<T>::iterator it) : v_(v), it_(it) {}


          FirstDimensionMajorIterator &operator++() {
            ++it_;
            return *this;
          }


          FirstDimensionMajorIterator operator++(int) {
            FirstDimensionMajorIterator temp = *this;
            ++it_;
            assert(temp != *this);
            return temp;
          }

           T &operator*() const {
            return *it_; 
           }

           friend
           bool operator==(const FirstDimensionMajorIterator &fdi1, const FirstDimensionMajorIterator &fdi2) {
             return fdi1.it_ == fdi2.it_;
           }

           friend
           bool operator!=(const FirstDimensionMajorIterator &fdi1, const FirstDimensionMajorIterator &fdi2) {
             return fdi1.it_ != fdi2.it_;
           }
      };
  };
  
  /* recursive variadic template */
  template <typename T, size_t N, size_t S, size_t ... Rest>
  class Array<T, N, S, Rest ...>  {


    /* friend(s) */
    template <typename U, size_t ... Dims>
    friend class Array;


    private:
      std::vector<Array<T, S, Rest...>> v = std::vector<Array<T, S, Rest...>>(N);


    public:
      using ValueType = T;
      class FirstDimensionMajorIterator;


      Array () = default;


      Array (const Array &arr) {
          v = arr.v;
      }


      Array &operator=(const Array &arr) {
          v = arr.v;
        return *this;
      }

  
      template <typename U>
      Array (const Array<U, N, S, Rest...> &arr) {
          for (size_t i = 0; i < N; i++) 
            v.at(i) = arr.v.at(i);
      }

  
      template <typename U>
      Array &operator=(const Array<U, N, S, Rest...> &arr) {
          for (size_t i = 0; i < N; i++) 
            v.at(i) = arr.v.at(i);
        return *this;
      }


      Array<T, S, Rest...> &operator[](size_t n) {
        try {
          return v.at(n);
        } catch (std::out_of_range) {
          throw OutOfRange();
        }
      }


      const Array<T, S, Rest...> &operator[](size_t n) const {
         try {
          return v.at(n);
        } catch (std::out_of_range) {
          throw OutOfRange();
        }
      }


      FirstDimensionMajorIterator fmbegin() {
        return FirstDimensionMajorIterator(v, v.begin(), v.end());
      }


      FirstDimensionMajorIterator fmend() {
        return FirstDimensionMajorIterator(v, v.end(), v.end());
      }


      class FirstDimensionMajorIterator {
        public:
          std::vector<Array<T, S, Rest...>> v_;
          typename std::vector<Array<T, S, Rest...>>::iterator it_, end_;
          typename Array<T, S, Rest...>::FirstDimensionMajorIterator cur_lower, cur_end;


          FirstDimensionMajorIterator(std::vector<Array<T, S, Rest...>> &v, 
          typename std::vector<Array<T, S, Rest...>>::iterator it, 
          typename std::vector<Array<T, S, Rest...>>::iterator end
          ) : v_(v), it_(it), end_(end) {
            if (it_ != end_) {
              cur_lower = (*it_).fmbegin();
              cur_end = (*it_).fmend();
            }
          }


          FirstDimensionMajorIterator() {}


          FirstDimensionMajorIterator &operator++() {
            if (it_ != end_) {
              if (cur_lower != cur_end) ++cur_lower;
              if (cur_lower == cur_end)  {
                ++it_;
                if (it_ != end_) {
                  cur_lower = (*it_).fmbegin();
                  cur_end = (*it_).fmend();
                }
              }
            }
            return *this;
          }


          FirstDimensionMajorIterator operator++(int) {
            FirstDimensionMajorIterator temp = *this;
            if (it_ != end_) {
              if (cur_lower != cur_end) ++cur_lower;
              if (cur_lower == cur_end)  {
                ++it_;
                if (it_ != end_) {
                  cur_lower = (*it_).fmbegin();
                  cur_end = (*it_).fmend();
                }
              }
            }
            return temp;
          }

           T &operator*() const {
            return *cur_lower; 
           }

           friend
           bool operator==(const FirstDimensionMajorIterator &fdi1, const FirstDimensionMajorIterator &fdi2) {
             return fdi1.it_ == fdi2.it_;
           }


           friend
           bool operator!=(const FirstDimensionMajorIterator &fdi1, const FirstDimensionMajorIterator &fdi2) {
             return fdi1.it_ != fdi2.it_;
           }
      };
  };
}
