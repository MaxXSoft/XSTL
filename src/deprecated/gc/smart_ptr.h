#ifndef XSTL_GC_SMART_PTR_H_
#define XSTL_GC_SMART_PTR_H_

#include <utility>
#include <cstddef>

#include "gc/gc_object.h"

namespace xstl::_gc {

template <typename T>
class SmartPtr {
 public:
  explicit SmartPtr(xstl::SmartGC *gc, bool root, GCObject *parent, T *ptr)
      : gc_(gc),
        root_(root),
        object_(new GCObject(parent, ptr, [gc](GCObject *gco, void *ptr) {
          gc->DelObjs(gco);
          delete static_cast<T *>(ptr);
        })) {
    gc_->AddObjs(object_);
    if (root_) gc_->AddObjs(object_, true);
  }

  SmartPtr() : gc_(nullptr), root_(false), object_(nullptr) {}
  SmartPtr(std::nullptr_t) : gc_(nullptr), root_(false), object_(nullptr) {}

  SmartPtr(const SmartPtr<T> &smart)
      : gc_(smart.gc_), root_(false), object_(smart.object_) {
    if (object_) object_->IncReference();
  }

  SmartPtr(SmartPtr<T> &&smart) noexcept
      : gc_(smart.gc_), root_(smart.root_), object_(smart.object_) {
    smart.gc_ = nullptr;
    smart.root_ = false;
    smart.object_ = nullptr;
  }

  ~SmartPtr() {
    if (root_) gc_->DelObjs(object_, true);
    DecAndRelease();
  }

  SmartPtr<T> &operator=(const SmartPtr<T> &smart) {
    if (this != &smart) {
      if (smart.object_) smart.object_->IncReference();
      if (root_) {  // TODO: problems?
        gc_->DelObjs(object_, true);
        if (!smart.root_ && smart.gc_)
          smart.gc_->AddObjs(smart.object_, true);
      }
      DecAndRelease();
      gc_ = smart.gc_;
      object_ = smart.object_;
    }
    return *this;
  }

  SmartPtr<T> &operator=(SmartPtr<T> &&smart) noexcept {
    if (this != &smart) {
      gc_ = smart.gc_;
      root_ = smart.root_;
      object_ = smart.object_;
      smart.gc_ = nullptr;
      smart.root_ = false;
      smart.object_ = nullptr;
    }
    return *this;
  }

  T &operator*() const noexcept {
    return *static_cast<T *>(object_->ptr());
  }

  T *operator->() const noexcept { return &this->operator*(); }

  explicit operator bool() const noexcept {
    return object_ && object_->ptr();
  }

  template <typename U, typename... Args>
  SmartPtr<U> make_smart(Args &&... args) {
    return SmartPtr<U>(gc_, false, object_,
                       new U(std::forward<Args>(args)...));
  }

  T *get() const { return object_ ? &this->operator*() : nullptr; }
  bool unique() const { return object_ ? object_->Unique() : false; }

 private:
  void DecAndRelease() {
    if (object_ && !object_->DecReference()) {
      delete object_;
      object_ = nullptr;
    }
  }

  xstl::SmartGC *gc_;
  bool root_;
  GCObject *object_;
};

}  // namespace xstl::_gc

#endif  // XSTL_GC_SMART_PTR_H_
