#ifndef NODE_H
#define NODE_H

#include<vector>
#include<iostream>

class node{
 private:
  int id;
  std::vector<node*> adj_list;
  bool reciprocal_add(const std::vector<node*>::iterator, node*);
 public:
  node(const int);
  int get_id();
  std::vector<node*> get_neighbors();
  void print();
  bool add_neighbor(node*);
  bool operator==(node);
  bool operator<(const node);
};

#endif
