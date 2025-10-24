# Compile and run competitive programming code

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

SRC = problems/range_minimum_query/range_minimum_query.cpp
OUT = $(basename $(notdir $(SRC)))
SRCDIR = $(dir $(SRC))
INFILE = $(SRCDIR)input.txt
OUTFILE = $(SRCDIR)output.txt

build:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(OUT)

run: build
	./$(OUT) < $(INFILE) > $(OUTFILE)

clean:
	rm -f $(OUT)
