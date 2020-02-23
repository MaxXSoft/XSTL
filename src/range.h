#ifndef XSTL_RANGE_H_
#define XSTL_RANGE_H_

#include <functional>
#include <cassert>

namespace xstl {

// NumTy: a type that can hold a number, such as 'int' or 'long'
template <typename NumTy = int>
class Range {
 public:
  using IterFunc = std::function<bool(NumTy &)>;

  Range(const Range &range) = delete;
  Range(NumTy stop) : start_(0), stop_(stop), step_(1), iter_(nullptr) {}
  Range(NumTy start, NumTy stop)
      : start_(start), stop_(stop), step_(1), iter_(nullptr) {}
  Range(NumTy start, NumTy stop, NumTy step)
      : start_(start), stop_(stop), step_(step), iter_(nullptr) {}
  Range(NumTy start, IterFunc &&iter)
      : start_(start), step_(0), iter_(iter) {}
  ~Range() {}

  class RangeIterator {
   public:
    RangeIterator(NumTy value, NumTy step)
        : value_(value), step_(step), iter_(nullptr), first_call_(true) {}
    RangeIterator(IterFunc iter) : iter_(iter) {}
    ~RangeIterator() {}

    // TODO: consider reimplementing this in an elegant way
    bool operator!=(const RangeIterator &it) {
      if (it.iter_) {
        assert(!iter_);
        if (first_call_) return !(first_call_ = false);
        return it.iter_(value_);
      }
      else {
        return value_ != it.value_;
      }
    }

    const RangeIterator &operator++() {
      assert(!iter_);
      value_ += step_;
      return *this;
    }

    NumTy operator*() const { return value_; }

   private:
    NumTy value_, step_;
    IterFunc iter_;
    bool first_call_;
  };

  RangeIterator begin() const { return RangeIterator(start_, step_); }
  RangeIterator end() const {
    return iter_ ? RangeIterator(iter_) : RangeIterator(stop_, step_);
  }

 private:
  NumTy start_, stop_, step_;
  IterFunc iter_;
};

}  // namespace xstl

#endif  // XSTL_RANGE_H_
