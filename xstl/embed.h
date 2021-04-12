#ifndef XSTL_EMBED_H_
#define XSTL_EMBED_H_

#include "os.h"

// special treatment for Mach-O
#ifdef XSTL_OS_MACOS
  #define __XSTL_EMBED_IMPL_SECTION ".const_data"
  #define __XSTL_EMBED_IMPL_MANGLE  "_"
#else
  #define __XSTL_EMBED_IMPL_SECTION ".section .rodata"
  #define __XSTL_EMBED_IMPL_MANGLE  ""
#endif

// special treatment for PE/COFF
#ifdef XSTL_OS_WINDOWS
  #define __XSTL_EMBED_IMPL_PREVIOUS  ".text"
#else
  #define __XSTL_EMBED_IMPL_PREVIOUS  ".previous"
#endif

// embedding file as null-terminated string
#define XSTL_EMBED_STR(name, path)         \
  extern const char name[];                \
  asm(__XSTL_EMBED_IMPL_SECTION "\n"       \
      __XSTL_EMBED_IMPL_MANGLE #name ":\n" \
      ".incbin \"" path "\"\n"             \
      ".byte 0\n"                          \
      __XSTL_EMBED_IMPL_PREVIOUS "\n")

#endif  // XSTL_EMBED_H_
