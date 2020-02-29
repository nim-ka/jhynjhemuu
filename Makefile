TARGET = jhynjhemuu

OPTFLAGS ?=

CXX ?= g++
CXXFLAGS := -Wall -std=c++17

BUILD_DIR := build

DUMMY != mkdir -p $(BUILD_DIR)

SRC_DIRS := src src/r4300i
CXX_FILES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
INC_FLAGS := -Iinclude $(foreach dir,$(SRC_DIRS),-I$(dir))

$(BUILD_DIR)/$(TARGET): $(CXX_FILES)
	$(CXX) $(INC_FLAGS) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: clean
