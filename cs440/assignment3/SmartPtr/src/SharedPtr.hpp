#ifndef AUSTIN_WARD_SHARED_PTR
#define AUSTIN_WARD_SHARED_PTR


#include <thread>
#include <mutex>


namespace cs540 {

  static std::mutex io_mutex;

  template <typename T>
  class SharedPtr {

    template <typename U>
    friend class SharedPtr;
    template <typename T1, typename T2>
    friend SharedPtr<T1> static_pointer_cast(const SharedPtr<T2> &sp);
    template <typename T1, typename T2>
    friend SharedPtr<T1> dynamic_pointer_cast(const SharedPtr<T2> &sp);


    private:
      T *obj_;
      size_t *count_;
      void (*obj_dtor_) (const void*);
      void *address_;


      void dtor_() {
        if (obj_ != nullptr) {
          if (!--(*count_)) {
            delete count_;
            obj_dtor_(address_);
            obj_ = nullptr;
          }
        }
      }


      template <typename U> 
      SharedPtr(const SharedPtr<U> &p, T* o) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = o;
        address_ = p.address_;
        count_ = p.count_;
        obj_dtor_ = p.obj_dtor_;
        if (p) (*count_)++;
      }


    public:
      SharedPtr() : obj_(nullptr), count_(nullptr), obj_dtor_(nullptr) {}


      ~SharedPtr() { 
        std::lock_guard<std::mutex> lock(io_mutex);
        dtor_();
      }


      template <typename U> 
      explicit SharedPtr(U *obj) : obj_(obj), count_(new size_t(1)) {
        std::lock_guard<std::mutex> lock(io_mutex);
        address_ = obj;
        obj_dtor_ = [](const void* o) {
          auto og = static_cast<const U*>(o);
          delete og;
        };
      }


      SharedPtr(const SharedPtr &p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = p.obj_;
        address_ = p.address_;
        count_ = p.count_;
        obj_dtor_ = p.obj_dtor_;
        if (p) (*count_)++;
      }

      
      template <typename U> 
      SharedPtr(const SharedPtr<U> &p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = p.obj_;
        address_ = p.address_;
        count_ = p.count_;
        obj_dtor_ = p.obj_dtor_;
        if (p) (*count_)++;
      }


      SharedPtr(SharedPtr &&p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = std::move(p.obj_);
        address_ = std::move(p.address_);
        count_ = std::move(p.count_);
        obj_dtor_ = std::move(p.obj_dtor_);
        p.obj_ = nullptr;
        p.address_  = nullptr;
        p.count_ = nullptr;
        p.obj_dtor_ = nullptr;
      }


      template <typename U> 
      SharedPtr(SharedPtr<U> &&p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = std::move(p.obj_);
        address_ = std::move(p.address_);
        count_ = std::move(p.count_);
        obj_dtor_ = std::move(p.obj_dtor_);
        p.obj_ = nullptr;
        p.address_  = nullptr;
        p.count_ = nullptr;
        p.obj_dtor_ = nullptr;
      }


      SharedPtr &operator=(const SharedPtr &p) {
        std::lock_guard<std::mutex> lock(io_mutex);
          dtor_();
          obj_ = p.obj_;
        address_ = p.address_;
          count_ = p.count_;
          obj_dtor_ = p.obj_dtor_;
          if (p) (*count_)++;
        return *this;
      }


      template <typename U>
      SharedPtr<T> &operator=(const SharedPtr<U> &p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        dtor_();
        obj_ = p.obj_;
        address_ = p.address_;
        count_ = p.count_;
        obj_dtor_ = p.obj_dtor_;
        if (p) (*count_)++;
        return *this;
      }


      SharedPtr &operator=(SharedPtr &&p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = std::move(p.obj_);
        address_ = std::move(p.address_);
        count_ = std::move(p.count_);
        obj_dtor_ = std::move(p.obj_dtor_);
        p.obj_ = nullptr;
        p.address_  = nullptr;
        p.count_ = nullptr;
        p.obj_dtor_ = nullptr;
        return *this;
      }


      template <typename U>
      SharedPtr<T> &operator=(SharedPtr<U> &&p) {
        std::lock_guard<std::mutex> lock(io_mutex);
        obj_ = std::move(p.obj_);
        address_ = std::move(p.address_);
        count_ = std::move(p.count_);
        obj_dtor_ = std::move(p.obj_dtor_);
        p.obj_ = nullptr;
        p.address_  = nullptr;
        p.count_ = nullptr;
        p.obj_dtor_ = nullptr;
        return *this;
      }


      T *operator->() const {
        return obj_;
      }


      T &operator*() const {
        return *obj_;
      }


      T *get() const {
        return obj_;
      }


      explicit operator bool() const {
        return obj_ != nullptr;
      }


      void reset() {
        std::lock_guard<std::mutex> lock(io_mutex);
        dtor_();
        obj_ = nullptr;
        count_ = nullptr;
        obj_dtor_ = nullptr;
      }


      template <typename U> 
      void reset(U *obj) {
        std::lock_guard<std::mutex> lock(io_mutex);
        dtor_();
        obj_ = obj;
        address_ = obj;
        count_ = new size_t(1);
        obj_dtor_ = [](const void* o) {
          auto og = static_cast<const U*>(o);
          delete og;
        };
      }
  };


  template <typename T1, typename T2>
  bool operator==(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {
    return p1.get() == p2.get();
  }


  template <typename T>
  bool operator==(const SharedPtr<T> &p, std::nullptr_t) {
    return p.get() == nullptr;
  }


  template <typename T>
  bool operator==(std::nullptr_t, const SharedPtr<T> &p) {
    return p.get() == nullptr;
  }


  template <typename T1, typename T2>
  bool operator!=(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2) {
    return p1.get() != p2.get();
  }


  template <typename T>
  bool operator!=(const SharedPtr<T> &p, std::nullptr_t) {
    return p.get() != nullptr;
  }


  template <typename T>
  bool operator!=(std::nullptr_t, const SharedPtr<T> &p) {
    return p.get() != nullptr;
  }


  template <typename T, typename U>
  SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp) {
    T* p = static_cast<T*>(sp.get());
    return SharedPtr<T>(sp, p);
  }


  template <typename T, typename U>
  SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp) {
    if (T* p = dynamic_cast<T*>(sp.get())) {
      return SharedPtr<T>(sp, p);
    } else {
      return SharedPtr<T>();
    }
  }
}


#endif
