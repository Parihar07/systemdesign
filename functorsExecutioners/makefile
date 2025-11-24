# Makefile for Concurrency examples
# Usage: make FILE=filename.cpp run

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
TARGET = program

# Default file if not specified
# Start with the simplest example by default
FILE ?= 00_single_thread_basics.cpp

all: build

build:
	@echo "Compiling $(FILE)..."
	@$(CXX) $(CXXFLAGS) $(FILE) -o $(TARGET)
	@echo "Build successful!"

run: build
	@echo "\n=== Running $(FILE) ===\n"
	@./$(TARGET)

clean:
	@rm -f $(TARGET)
	@echo "Cleaned build artifacts"

.PHONY: all build run clean
