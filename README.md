# XSTL

Write some lightweight gadgets to eXtend STL ...

## Gadgets

* **[progress.h](xstl/progress.h)**: display progress bar in terminal
* **[singleton.h](xstl/singleton.h)**: a base template class of singleton (thread-safe)
* **[os.h](xstl/os.h)**: macros about platform/compiler
* **[cast.h](xstl/cast.h)**: casting between different pointer types or endians
* **[argparse.h](xstl/argparse.h)**: command line argument parser
* **[style.h](xstl/style.h)**: set output style of `std::ostream`
* **[guard.h](xstl/guard.h)**: do something when leaving current block (used to generate type info and IR in *[TinyLang](https://github.com/MaxXSoft/TinyMIPS/blob/master/src/compiler/front/analyzer.h)*, combining with visitor pattern)
* **[nested.h](xstl/nested.h)**: nested map, supported recursive lookup
* **[bitvalue.h](xstl/bitvalue.h)**: bit extraction/concatenation, can be used in both runtime and compile time
* **[bitpat.h](xstl/bitpat.h)**: bitwise pattern match
* **[segfault.h](xstl/segfault.h)**: `try-catch` mechanism for segmentation fault

### Deprecated Gadgets

We do not recommend you to use the following gadgets in your project since they are too shabby:

* **[raii.h](xstl/deprecated/raii.h)**: using *RAII* to release resources automatically
* **[str_hash.h](xstl/deprecated/str_hash.h)**: get the hash value of a string constant while compile time
* **[argh.h](xstl/deprecated/argh.h)**: parse command line arguments
* **[gc/gc.h](xstl/deprecated/gc/gc.h)**: using *reference counting* and *mark-and-sweep* garbage collecting techniques to release resources, you can use it just like using `std::shared_ptr`!
* **[range.h](xstl/deprecated/range.h)**: can be used in a range-based for loop, like 'range()' in Python

## Examples

See [examples](examples) directory.

## Requirement

C++17 required.

## Copyright and License

Copyright (C) 2010-2020 MaxXSoft. License MIT.
