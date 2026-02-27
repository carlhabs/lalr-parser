CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2
TARGET   := tp

SRCS := main.cpp lexer.cpp symbole.cpp automate.cpp
OBJS := $(addprefix build/,$(SRCS:.cpp=.o))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build