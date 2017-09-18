# XSTL

write some gadgets to eXtend STL ...

---

## Gadgets

* **[raii.h](src/raii.h)**: using *RAII* to release resources automatically
* **[str_hash.h](src/str_hash.h)**: get the hash value of a string constant while compile time
* **[argh.h](src/argh.h)**: parse command line arguments
* **[gc/smart_gc.h](src/gc/smart_gc.h)**: using *reference counting* and *mark-and-sweep* garbage collecting techniques to release resources, you can use it just like using `std::shared_ptr`!

## Examples

see [example](example/) dir.

## Requirement

C++17 required.

## Copyright and License

Copyright (C) 2010-2017 MaxXSoft. License GPL-3.0. 
