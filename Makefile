# external parameters
DEBUG = 0
OPT_LEVEL = 2

# judge if is debug mode
ifeq ($(DEBUG), 0)
	DEBUG_ARG = -DNDEBUG
	OPT_ARG = -O$(OPT_LEVEL)
else
	DEBUG_ARG = -g
	OPT_ARG = 
endif

# directories
TOP_DIR = $(shell if [ "$$PWD" != "" ]; then echo $$PWD; else pwd; fi)
TARGET_DIR = $(TOP_DIR)/build
INC_DIR = $(TOP_DIR)/src
SRC_DIR = $(TOP_DIR)/examples

# C++ compiler
CXXFLAGS := $(DEBUG_ARG) $(OPT_ARG)
CXXFLAGS += -Wall -Werror -std=c++17 -I$(INC_DIR)
CXX := clang++ $(CXXFLAGS)

# files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
TARGETS := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%, $(SRC_FILES))

.PHONY: all clean

all: $(TARGET_DIR) ${TARGETS}

clean:
	-rm $(TARGETS)

$(TARGET_DIR):
	mkdir $(TARGET_DIR)

$(TARGET_DIR)/%: $(SRC_DIR)/%.cpp
	-mkdir -p $(dir $@)
	$(CXX) $^ -o $@
