#ifndef XSTL_EMBED_H_
#define XSTL_EMBED_H_

#define XSTL_EMBED_STR(name, path)           \
  extern const char name[];                  \
  asm(".section .rodata\n" \
      #name ":\n"                            \
      ".incbin \"" path "\"\n"               \
      ".byte 0\n"                            \
      ".text\n")

#endif  // XSTL_EMBED_H_
