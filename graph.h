#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>
#include"node.h"
#include"edge.h"

class graph{
 private:
  std::vector<node*> nodes;
  std::vector<edge*> edges;
  bool add_node_helper(const std::vector<node*>::iterator, node*);
  bool add_edge_helper(const std::vector<edge*>::iterator, edge*);
  bool contains_node(node*);
 public:
  graph();
  bool add_node(node*);
  bool add_edge(edge*);
  std::vector<node*> get_nodes();
  std::vector<edge*> get_edges();
  node* get_node(int);
  edge* get_edge(int, int);
  void print();
  void create_dot_file();
};

#endif
