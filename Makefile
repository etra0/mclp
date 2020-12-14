CXX = g++
OUTPUT_PATH = bin
SOURCE_PATH = src

FLAGS = -g -Wall --std=c++17 -O0 -I$(SOURCE_PATH)
EXECUTABLE = $(OUTPUT_PATH)/mclp

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE_PATH)/main.cpp $(OUTPUT_PATH)/parser.o
	$(CXX) $(FLAGS) -o $@ $^

$(OUTPUT_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	$(CXX) -c $(FLAGS) $< -o $@

clean:
	rm $(OUTPUT_PATH)/*
