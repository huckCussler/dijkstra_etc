CXX=g++
CXXFLAGS=-std=c++0x -Wall -g
OBJS=graph.o node.o edge.o random_graph_generator.o min_heap.o dijkstra.o

all: compile run

compile: main.o $(OBJS)
	$(CXX) -g main.o $(OBJS) -o main

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

graph.o: graph.cc
	$(CXX) $(CXXFLAGS) -c graph.cc

node.o: node.cc
	$(CXX) $(CXXFLAGS) -c node.cc

edge.o: edge.cc
	$(CXX) $(CXXFLAGS) -c edge.cc

random_graph_generator.o: random_graph_generator.cc
	$(CXX) $(CXXFLAGS) -c random_graph_generator.cc

min_heap.o: min_heap.cc
	$(CXX) $(CXXFLAGS) -c min_heap.cc

dijkstra.o: dijkstra.cc
	$(CXX) $(CXXFLAGS) -c dijkstra.cc

run: main
	./main

clean:
	rm -f *.o main tester

compile_test: tester.o $(OBJS)
	$(CXX) $(CXXFLAGS) tester.o $(OBJS) -o tester

tester.o: tester.cc
	$(CXX) $(CXXFLAGS) -c tester.cc

run_test: tester
	./tester

test: compile_test run_test

