CXX=g++
WFLAGS=-Wall -Wextra 
DEBUG_FLAGS=-g -O0 
IFLAGS=-I include/ -std=c++17
SRC_FILES=src/*.cpp

BUILDDIR=build

main: builddir	
	$(CXX) $(DEBUG_FLAGS) $(IFLAGS) $(SRC_FILES) -o $(BUILDDIR)/main


builddir:
	mkdir -p build