CXX=g++
WFLAGS=-Wall -Wextra
DEBUG_FLAGS=-g -O0
IFLAGS=-I include/
SRC_FILES=src/main.cpp src/graph.cpp src/neighbors.cpp

BUILDDIR=build

main: builddir	
	$(CXX) $(DEBUG_FLAGS) $(IFLAGS) $(SRC_FILES) -o $(BUILDDIR)/main


builddir:
	mkdir -p build