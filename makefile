CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD 
LDFLAGS = -lX11
EXEC = chess
CCFILES = $(shell find . -name '*.cc')
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(OBJECTS:.o=.d)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

-include $(DEPENDS)

.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS) $(DEPENDS)