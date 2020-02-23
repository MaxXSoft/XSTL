# XSTL

Write some gadgets to eXtend STL ...

## Gadgets

* **[progress.h](src/progress)**: display progress bar in terminal.

### Deprecated

* **[raii.h](src/deprecated/raii.h)**: using *RAII* to release resources automatically
* **[str_hash.h](src/deprecated/str_hash.h)**: get the hash value of a string constant while compile time
* **[argh.h](src/deprecated/argh.h)**: parse command line arguments
* **[gc/gc.h](src/deprecated/gc/gc.h)**: using *reference counting* and *mark-and-sweep* garbage collecting techniques to release resources, you can use it just like using `std::shared_ptr`!
* **[range.h](src/deprecated/range.h)**: can be used in a range-based for loop, like 'range()' in Python

## Examples

See [example](example/) dir.

## Requirement

C++17 required.

## Copyright and License

Copyright (C) 2010-2020 MaxXSoft. License GPLv3.
