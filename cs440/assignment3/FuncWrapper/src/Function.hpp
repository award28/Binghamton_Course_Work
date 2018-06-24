#ifndef AUSTIN_WARD_FUNCTION
#define AUSTIN_WARD_FUNCTION

#include <functional>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <cassert>

namespace cs540 {
  
  /* Exception */
  class BadFunctionCall {
    public:
      BadFunctionCall() {}
  };

  /* Allows specialization template */
  template <typename T>
  class Function;

  /* Specialization template */
  template <typename ResultType, typename ... ArgumentTypes> 
  class Function<ResultType(ArgumentTypes...)> {


    private:
      class Functor_Base {
        public:
          virtual ~Functor_Base() = default;
          virtual ResultType invoke(ArgumentTypes ...) = 0;
      };


      template <typename T>
      class Functor : public Functor_Base {
        private:


          T t_;


        public: 
          Functor(const T& t) : t_(t) {}
          ~Functor() override = default;

          ResultType invoke(ArgumentTypes ... args) override {
             return t_(args ...);
          };
      };


      bool callable_;
      std::shared_ptr<Functor_Base> func_;


    public:
      Function() : callable_(false) {} 
      template <typename T>
      Function(T t) : callable_(true), func_(std::make_shared<Functor<T>> (t)) {}
      Function(const Function &f) : callable_(f.callable_), func_(f.func_) {}
      template <typename T>
      Function &operator=(const Function &f) { 
        callable_ = f.callable_;
        func_ = f.func_;
        return *this;
      }

      ResultType operator()(ArgumentTypes... args) const {
        if (callable_) return func_->invoke(args...);
        throw BadFunctionCall();
      }

      explicit operator bool() const { return callable_; }

      friend
      bool operator==(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t) {
        return !f.callable_;
      }

      friend
      bool operator==(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f) {
        return !f.callable_;
      }

      friend
      bool operator!=(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t) {
        return f.callable_;
      }

      friend
      bool operator!=(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f) {
        return f.callable_;
      }
  };
}

#endif
