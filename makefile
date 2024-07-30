# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pthread
CPPFLAGS += -isystem /usr/lib/gtest/include

# Google Test settings
GTEST_DIR = /usr/lib/gtest
GTEST_LIB_DIR = /usr/lib
GTEST_LIBS = -lgtest -lgtest_main

# Build directory
BUILDDIR = build

# Executable and source files
EXEC = chess
CCFILES = $(shell find . -name '*.cc' -not -name 'implementationValidity.cc')
OBJECTS = $(patsubst %.cc,$(BUILDDIR)/%.o,$(CCFILES))
DEPENDS = $(patsubst %.o,$(BUILDDIR)/%.d,$(OBJECTS))

# Executable and source files for TESTING
EXEC2 = chess_test
CCFILES2 = $(shell find . -name '*.cc' -not -name 'test.cc')
OBJECTS2 = $(patsubst %.cc,$(BUILDDIR)/%.o,$(CCFILES2))
DEPENDS2 = $(patsubst %.o,$(BUILDDIR)/%.d,$(OBJECTS2))

all: $(EXEC) $(EXEC2)

# Target for the main executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) -lX11

# Target for the test executable
$(EXEC2): $(OBJECTS2)
	$(CXX) $(OBJECTS2) -o $(EXEC2) -lX11 -L$(GTEST_LIB_DIR) $(GTEST_LIBS)

# Rule to compile .cc files into .o files
$(BUILDDIR)/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Rule to include dependencies
-include $(DEPENDS)

# Phony targets
.PHONY: clean
clean:
	rm -f $(EXEC) $(EXEC2)
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/*.d
	rm -f $(BUILDDIR)/*/*.o $(BUILDDIR)/*/*.d

# Build Google Test if needed
GTEST_SRCS = $(GTEST_DIR)/src/gtest-all.cc $(GTEST_DIR)/src/gtest_main.cc

gtest-all.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc -o $(BUILDDIR)/gtest-all.o

gtest_main.o : $(GTEST_SRCS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc -o $(BUILDDIR)/gtest_main.o

gtest.a : $(BUILDDIR)/gtest-all.o
	$(AR) rcs $@ $^

gtest_main.a : $(BUILDDIR)/gtest-all.o $(BUILDDIR)/gtest_main.o
	$(AR) rcs $@ $^

# Targets to build Google Test library
gtest: gtest.a gtest_main.a
