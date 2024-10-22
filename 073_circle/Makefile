# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -pedantic

# Name of the executable
EXEC = circles

# Source and header files
SRCS = main.cpp circle.cpp point.cpp
HEADERS = circle.hpp point.hpp

# Object files
OBJS = main.o circle.o point.o

# Default target: link the object files and create the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile each .cpp file into an object file
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target: remove the executable and object files
.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJS)
