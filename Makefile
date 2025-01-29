# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g

# Target executable and source file
TARGET := main
SRC := main.cpp

run:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@./main < int

a:
	$(CXX) $(CXXFLAGS) a.cpp -o a
	@./a < int

b:
	$(CXX) $(CXXFLAGS) b.cpp -o b
	@./b < int

c:
	$(CXX) $(CXXFLAGS) c.cpp -o c
	@./c < int

# Rule to clean up build artifacts
.PHONY: clean
clean:
	rm -f $(TARGET)
