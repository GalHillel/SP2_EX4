CXX = g++
CXXFLAGS = -std=c++17 -Iinclude
SRCS = src/complex.hpp src/node.hpp src/tree.hpp main.cpp
OBJS = $(SRCS:src/%.cpp=obj/%.o)
DEPS = $(wildcard src/*.hpp)

all: tree_demo

tree: tree_demo
	./tree_demo

tree_demo: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

obj/%.o: src/%.cpp $(DEPS) | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p obj

clean:
	rm -f tree_demo obj/*.o

.PHONY: all clean
