# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2

# Check if FILE is specified
ifdef FILE
    # Compile only the specified file
    SRCS = $(FILE)
    TARGET = $(basename $(FILE))
else
    # Compile all .cpp files in current directory
    SRCS = $(wildcard *.cpp)
    TARGET = $(notdir $(CURDIR)).out
endif

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build (with debug symbols, no optimization)
debug: CXXFLAGS = -std=c++17 -Wall -Wextra -g -O0
debug: clean $(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET) *.out

# Rebuild everything
rebuild: clean all

# Show detected files (useful for debugging makefile)
info:
	@echo "Directory: $(CURDIR)"
	@echo "Target: $(TARGET)"
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"

# Phony targets
.PHONY: all run debug clean rebuild info