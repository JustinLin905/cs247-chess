# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
LDFLAGS = -lX11

# Google Test settings
GTEST_DIR = /path/to/googletest
GTEST_INCLUDE_DIR = $(GTEST_DIR)/include
GTEST_LIB_DIR = $(GTEST_DIR)/lib
GTEST_LIBS = -lgtest -lgtest_main -pthread

# Executable and source files
EXEC = chess
CCFILES = $(shell find . -name '*.cc')
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)

# Target for the main executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Target for Google Test executable
test: $(OBJECTS) $(GTEST_LIB_DIR)/libgtest.a $(GTEST_LIB_DIR)/libgtest_main.a
	$(CXX) $(OBJECTS) -o test $(GTEST_LIBS) $(LDFLAGS)

# Rule to include dependencies
-include $(DEPENDS)

# Phony targets
.PHONY: clean test

# Clean target
clean:
	rm -f $(EXEC) $(OBJECTS) $(DEPENDS) test

# Rule to build Google Test from source (if needed)
$(GTEST_LIB_DIR)/libgtest.a: $(GTEST_DIR)
	cd $(GTEST_DIR) && mkdir -p build && cd build && cmake .. && make
	touch $@

$(GTEST_LIB_DIR)/libgtest_main.a: $(GTEST_DIR)
	cd $(GTEST_DIR) && mkdir -p build && cd build && cmake .. && make
	touch $@
