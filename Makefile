CXX = clang++
OUTPUT_PATH = bin
SOURCE_PATH = src
MAIN = $(SOURCE_PATH)/main.cpp

WARNINGS = -Wall -Weffc++ -pedantic \
	-pedantic-errors -Wextra -Wcast-align \
	-Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion \
	-Wdisabled-optimization \
	-Wfloat-equal -Wformat  -Wformat=2 \
	-Wformat-nonliteral -Wformat-security  \
	-Wformat-y2k \
	-Wimport  -Winit-self  -Winline \
	-Winvalid-pch   \
	-Wlong-long -Wmissing-braces \
	-Wmissing-field-initializers -Wmissing-format-attribute   \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked  -Wparentheses  -Wpointer-arith \
	-Wredundant-decls -Wreturn-type \
	-Wsequence-point  -Wshadow -Wsign-compare  -Wstack-protector \
	-Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
	-Wswitch-enum -Wtrigraphs  -Wuninitialized \
	-Wunknown-pragmas  -Wunreachable-code -Wunused \
	-Wunused-function  -Wunused-label  -Wunused-parameter \
	-Wunused-value  -Wunused-variable  -Wvariadic-macros \
	-Wvolatile-register-var  -Wwrite-strings 

STACKTRACE = -fsanitize=address,undefined -fno-omit-frame-pointer
FLAGS = -g $(WARNINGS) $(STACKTRACE) --std=c++17 -O0 -I$(SOURCE_PATH) $(CFLAGS)
FLAGS_RELEASE = --std=c++17 -O3 -I$(SOURCE_PATH) $(CFLAGS)

EXECUTABLE = $(OUTPUT_PATH)/mclp

.PHONY: all clean run release

all: $(OUTPUT_PATH) $(EXECUTABLE)

release: FLAGS = $(FLAGS_RELEASE)
release: all

run: all
	$(OUTPUT_PATH)/mclp

$(OUTPUT_PATH):
	mkdir $(OUTPUT_PATH)

$(EXECUTABLE): $(MAIN) $(patsubst $(SOURCE_PATH)/%.cpp, $(OUTPUT_PATH)/%.o, $(filter-out $(MAIN),$(wildcard $(SOURCE_PATH)/*.cpp)))
	$(CXX) $(FLAGS) -o $@ $^

$(OUTPUT_PATH)/%.o: $(SOURCE_PATH)/%.cpp $(SOURCE_PATH)/mclp/%.hpp
	$(CXX) $(FLAGS) -c  $< -o $@

clean:
	rm -rf $(OUTPUT_PATH)/*
