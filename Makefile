# Makefile for compiling a Raylib C++ project

# Compiler and flags
CXX = clang
# CXXFLAGS = --std=c++11

# Raylib include and lib paths
INCLUDES = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Source and output
SRC = main.c
OUT = main

# Build target
all:
	$(CXX)  $(SRC) -o $(OUT) $(INCLUDES) $(LDFLAGS) $(LIBS)

# Clean target
clean:
	rm -f $(OUT)

