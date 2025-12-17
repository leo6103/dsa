# Compile and run competitive programming code

.PHONY: build run test clean

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

# Project root (directory containing this Makefile), used so binaries
# always go under the top-level out/ even if make is run from subdirs.
ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
OUT_DIR := $(ROOT_DIR)/out

SRC = problems/leetcode123/solution.cpp
OUT = $(OUT_DIR)/$(basename $(notdir $(SRC)))
SRCDIR = $(dir $(SRC))
INFILE = $(SRCDIR)input.txt
OUTFILE = $(SRCDIR)output.txt
TEST_SRC = test.cpp
TEST_OUT = $(OUT_DIR)/test_runner

build:
	mkdir -p $(OUT_DIR)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(OUT)

run: build
	$(OUT) < $(INFILE) > $(OUTFILE)

test:
	mkdir -p $(OUT_DIR)
	$(CXX) $(TEST_SRC) $(CXXFLAGS) -o $(TEST_OUT)
	./$(TEST_OUT)

clean:
	rm -f $(OUT) $(TEST_OUT)
