#ifndef RANDOM_GRAPH_GENERATOR_H
#define RANDOM_GRAPH_GENERATOR_H

#include<utility>
#include<iostream>
#include<stdexcept>
#include<cstdlib>
#include<ctime>
#include"graph.h"

class random_graph_generator{
 private:
  double density;
  int node_count;
  std::pair<double, double> weight_range;
  bool should_add_edge();
  double make_weight();
 public:
  random_graph_generator(double, int, std::pair<double, double>);
  void print();
  graph *create_graph();
};

#endif
