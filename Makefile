# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = bin

# Find all .cpp files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Define the executable name (Added .exe for Windows)
TARGET = $(BIN_DIR)/AirportSim.exe

# Default rule
all: $(TARGET)

# Rule to link the program
$(TARGET): $(SOURCES)
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Clean rule (Windows style)
clean:
	@if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)

.PHONY: all clean