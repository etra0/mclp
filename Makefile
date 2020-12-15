CXX = g++
OUTPUT_PATH = bin
SOURCE_PATH = src

WARNINGS = -Wall -Weffc++ -pedantic \
	-pedantic-errors -Wextra -Wcast-align \
	-Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
	-Wdisabled-optimization \
	-Werror -Wfloat-equal -Wformat  -Wformat=2 \
	-Wformat-nonliteral -Wformat-security  \
	-Wformat-y2k \
	-Wimport  -Winit-self  -Winline \
	-Winvalid-pch   \
	-Wunsafe-loop-optimizations  -Wlong-long -Wmissing-braces \
	-Wmissing-field-initializers -Wmissing-format-attribute   \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked  -Wpadded -Wparentheses  -Wpointer-arith \
	-Wredundant-decls -Wreturn-type \
	-Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
	-Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
	-Wswitch-enum -Wtrigraphs  -Wuninitialized \
	-Wunknown-pragmas  -Wunreachable-code -Wunused \
	-Wunused-function  -Wunused-label  -Wunused-parameter \
	-Wunused-value  -Wunused-variable  -Wvariadic-macros \
	-Wvolatile-register-var  -Wwrite-strings 

FLAGS = -g $(WARNINGS) --std=c++17 -O0 -I$(SOURCE_PATH) 
EXECUTABLE = $(OUTPUT_PATH)/mclp

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE_PATH)/main.cpp $(OUTPUT_PATH)/parser.o
	$(CXX) $(FLAGS) -o $@ $^ -lstdc++

$(OUTPUT_PATH)/%.o: $(SOURCE_PATH)/%.cpp
	$(CXX) -c $(FLAGS) $< -o $@

clean:
	rm $(OUTPUT_PATH)/*
