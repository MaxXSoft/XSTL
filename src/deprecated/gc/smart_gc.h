// C++17 required

#ifndef XSTL_GC_SMART_GC_H_
#define XSTL_GC_SMART_GC_H_

#include <deque>

#include "deprecated/gc/gc_object.h"

namespace xstl {

namespace _gc {
template <typename T>
class SmartPtr;
}  // namespace _gc

template <typename T>
using SmartPtr = _gc::SmartPtr<T>;

class SmartGC {
 public:
  SmartGC() {}
  ~SmartGC() {
    if (!empty()) CollectGarbage();
  }

  template <typename T, typename... Args>
  SmartPtr<T> make_smart(Args &&... args) {
    return SmartPtr<T>(this, true, nullptr,
                       new T(std::forward<Args>(args)...));
  }

  void CollectGarbage() {
    for (const auto &i : root_objs_) {
      i->Trace();
    }
    for (const auto &i : managed_objs_) {
      if (i->marked()) {
        i->set_marked(false);
      }
      else {
        i->Release();
      }
    }
  }

  bool empty() const { return managed_objs_.empty(); }

 private:
  template <typename T>
  friend class _gc::SmartPtr;

  void AddObjs(_gc::GCObject *gco, bool root = false) {
    auto &obj_list = root ? root_objs_ : managed_objs_;
    obj_list.push_back(gco);
  }

  void DelObjs(_gc::GCObject *gco, bool root = false) {
    auto &obj_list = root ? root_objs_ : managed_objs_;
    for (auto &&i : obj_list) {
      if (i == gco) {
        i = obj_list.back();
        obj_list.pop_back();
        return;
      }
    }
  }

  std::deque<_gc::GCObject *> managed_objs_, root_objs_;
};

}  // namespace xstl

#endif  // XSTL_GC_SMART_GC_H_
