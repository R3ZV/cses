# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g

# Target executable and source file
TARGET := main
SRC := main.cpp

run:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@./main < int

# Rule to clean up build artifacts
.PHONY: clean
clean:
	rm -f $(TARGET)
