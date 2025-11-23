# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -Ilib
GUI_LDFLAGS := -Llib/ -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
CLI_LDFLAGS :=

# Directories
SRC_DIR := src
BUILD_DIR := build
GUI_TARGET := $(BUILD_DIR)/logic_calculator.exe
CLI_TARGET := $(BUILD_DIR)/logic_calculator_cli.exe

# Source files
GUI_SOURCES := $(SRC_DIR)/gui_main.cpp \
               $(SRC_DIR)/tokenizer.cpp \
               $(SRC_DIR)/parser.cpp \
               $(SRC_DIR)/evaluator.cpp \
               $(SRC_DIR)/tTable.cpp \
               $(SRC_DIR)/rayFunctions.cpp

CLI_SOURCES := $(SRC_DIR)/cli_main.cpp \
               $(SRC_DIR)/tokenizer.cpp \
               $(SRC_DIR)/parser.cpp \
               $(SRC_DIR)/evaluator.cpp \
               $(SRC_DIR)/tTable.cpp

# Default target (GUI version)
all: $(GUI_TARGET)

# GUI version
$(GUI_TARGET): $(GUI_SOURCES)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(GUI_SOURCES) $(GUI_LDFLAGS) -o $@

# CLI version
cli: $(CLI_TARGET)

$(CLI_TARGET): $(CLI_SOURCES)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CLI_SOURCES) $(CLI_LDFLAGS) -o $@

clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)

rebuild: clean all

run: $(GUI_TARGET)
	$(GUI_TARGET)

run-cli: $(CLI_TARGET)
	$(CLI_TARGET)

debug:
	$(CXXFLAGS) += -g -O0
	@echo GUI_SOURCES: $(GUI_SOURCES)
	@echo CLI_SOURCES: $(CLI_SOURCES)
	@echo GUI_TARGET: $(GUI_TARGET)
	@echo CLI_TARGET: $(CLI_TARGET)

.PHONY: all cli clean rebuild run run-cli debug