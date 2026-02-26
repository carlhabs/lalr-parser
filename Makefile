CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2
TARGET   := tp

SRCS := main.cpp lexer.cpp symbole.cpp automate.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe