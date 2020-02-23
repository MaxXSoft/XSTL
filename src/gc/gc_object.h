#ifndef XSTL_GC_GC_OBJECT_H_
#define XSTL_GC_GC_OBJECT_H_

#include <functional>
#include <deque>
#include <cstddef>

namespace xstl::_gc {

class GCObject {
 public:
  using Deleter = std::function<void(GCObject *, void *)>;

  GCObject(GCObject *parent, void *ptr, Deleter &&deleter)
      : parent_(parent), ptr_(ptr), deleter_(deleter),
        counter_(1), marked_(false) {
    ParentAdd();
  }

  ~GCObject() {
    ParentDel();
    Release();
  }

  void IncReference() { ++counter_; }

  // return true if ptr is not released
  bool DecReference() {
    if (counter_ && --counter_ == 0) Release();
    return counter_;
  }

  void Release() {
    if (ptr_) {
      auto temp = ptr_;
      ptr_ = nullptr;
      deleter_(this, temp);
    }
  }

  void Trace() {
    if (marked_) return;
    marked_ = true;
    for (const auto &i : obj_list_) {
      i->Trace();
    }
  }

  bool Unique() const { return ptr_ && (counter_ == 1); }

  void *ptr() const { return ptr_; }
  void set_marked(bool marked) { marked_ = marked; }
  bool marked() const { return marked_; }

 private:
  void ParentAdd() {
    if (parent_) parent_->obj_list_.push_back(this);
  }

  void ParentDel() {
    if (!parent_) return;
    for (auto &&i : parent_->obj_list_) {
      if (i == this) {
        i = parent_->obj_list_.back();
        parent_->obj_list_.pop_back();
        return;
      }
    }
  }

  GCObject *parent_;
  size_t counter_;
  void *ptr_;
  Deleter deleter_;
  bool marked_;
  std::deque<GCObject *> obj_list_;
};

}  // namespace xstl::_gc

#endif  // XSTL_GC_GC_OBJECT_H_
