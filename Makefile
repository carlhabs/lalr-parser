# GENERE AVEC IA

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2

TARGET        := tp
TEST_TARGET   := test_parser

SRC_DIR      := src
BUILD_DIR    := build

SRCS         := $(wildcard $(SRC_DIR)/*.cpp)
HDRS         := $(wildcard $(SRC_DIR)/*.h)
MAIN_SRC     := $(SRC_DIR)/main.cpp
TEST_SRC     := $(SRC_DIR)/test_parser.cpp

# OBJS pour tp : tous sauf test_parser.cpp
OBJS         := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter-out $(TEST_SRC),$(SRCS)))
# OBJS pour test_parser : tous sauf main.cpp
TEST_OBJS    := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter-out $(MAIN_SRC),$(SRCS)))

.PHONY: all clean test

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)
