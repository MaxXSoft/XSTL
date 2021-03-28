#ifndef XSTL_SEGFAULT_H_
#define XSTL_SEGFAULT_H_

#include <csetjmp>
#include <csignal>

/*
  try-catch feature for segmentation fault

  usage:
    TRY_SEGFAULT {
      // do something
    }
    CATCH_SEGFAULT {
      // catch segmentation fault here
    }
*/
#define TRY_SEGFAULT                                        \
  xstl::_segfault_impl::SegFaultGuard XSTL_SEGFAULT_CONCAT( \
      __xstl_segfault_guard, __COUNTER__);                  \
  if (!setjmp(xstl::_segfault_impl::segfault_jmp_point))
#define CATCH_SEGFAULT else
#define XSTL_SEGFAULT_CONCAT(x, y) XSTL_SEGFAULT_CONCAT_IMPL(x, y)
#define XSTL_SEGFAULT_CONCAT_IMPL(x, y) x ## y

// internal implementations
namespace xstl::_segfault_impl {

// segmentation fault handler
static std::jmp_buf segfault_jmp_point;
static void SegFaultHandler(int sig) {
  std::longjmp(segfault_jmp_point, 1);
}

// segmentation fault guard
class SegFaultGuard {
 public:
  SegFaultGuard() {
    std::signal(SIGSEGV, SegFaultHandler);
  }
  ~SegFaultGuard() {
    std::signal(SIGSEGV, SIG_DFL);
  }
};

}  // namespace xstl::_segfault_impl

#endif  // XSTL_SEGFAULT_H_
