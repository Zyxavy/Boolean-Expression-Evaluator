CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
SOURCES  := src/tokenizer.cpp  src/parser.cpp src/main.cpp
TARGET   := tokenizer_test

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)