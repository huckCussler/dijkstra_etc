#ifndef EDGE_H
#define EDGE_H

#include<utility>
#include<iostream>
#include<stdexcept>
#include"node.h"

class edge{
 private:
  std::pair<node*, node*> nodes;
  double weight;
  void swap_nodes();
 public:
  edge(std::pair<node*, node*>, const double);
  std::pair<node*, node*> get_nodes();
  double get_weight();
  bool operator==(edge);
  bool operator<(const edge);
  void print();
};

#endif
