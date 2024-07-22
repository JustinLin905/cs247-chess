CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = chess
CCFILES = $(shell find . -name '*.cc')
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)
	
-include $(DEPENDS)
.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS) $(DEPENDS)