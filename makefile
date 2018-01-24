export cc = g++
export std = c++1z
export opt_level = 2
export build_dir = build/
export debug = false

ifeq ($(debug), true)
	debug_arg = -g
	opt_arg = 
else
	debug_arg = 
	opt_arg = -O$(opt_level)
endif

exp_dir = example/

raii_targets = $(exp_dir)raii.cpp
raii_out = $(build_dir)raii

str_hash_targets = $(exp_dir)string_hash.cpp
str_hash_out = $(build_dir)hash

argh_targets = $(exp_dir)argh.cpp
argh_out = $(build_dir)argh

gc_targets = $(exp_dir)gc.cpp
gc_out = $(build_dir)gc

range_targets = $(exp_dir)range.cpp
range_out = $(build_dir)range

CC = $(cc) $(debug_arg) -std=$(std) $(opt_arg)

.PHONY: all example raii str_hash argh gc clean clean_dbg

all: example

example: raii str_hash argh gc range

raii: $(raii_targets)
	$(CC) $(raii_targets) -o $(raii_out)

str_hash:
	$(CC) $(str_hash_targets) -o $(str_hash_out)

argh:
	$(CC) $(argh_targets) -o $(argh_out)

gc:
	$(CC) $(gc_targets) -o $(gc_out)

range:
	$(CC) $(range_targets) -o $(range_out)

clean: clean_dbg
	rm $(raii_out) $(str_hash_out) $(argh_out) $(gc_out) $(range_out)

clean_dbg:
	-rm -r $(build_dir)*.dSYM
