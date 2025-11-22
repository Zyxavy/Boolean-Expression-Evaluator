# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -Ilib
LDFLAGS := -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows

# Directories
SRC_DIR := src
BUILD_DIR := build
TARGET := $(BUILD_DIR)/logic_calculator.exe

# All .cpp files that should be compiled
SOURCES :=	$(SRC_DIR)/main.cpp \
        	$(SRC_DIR)/tokenizer.cpp \
        	$(SRC_DIR)/parser.cpp \
			$(SRC_DIR)/evaluator.cpp \
			$(SRC_DIR)/tTable.cpp \
			$(SRC_DIR)/rayFunctions.cpp \
           

all: $(TARGET)

$(TARGET): $(SOURCES)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $@

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

rebuild: clean all

run: $(TARGET)
	$(TARGET)

debug:
	@echo SOURCES: $(SOURCES)
	@echo TARGET: $(TARGET)

.PHONY: all clean rebuild run debug