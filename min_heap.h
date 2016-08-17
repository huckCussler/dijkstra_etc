#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include<algorithm>
#include<stdexcept>
#include"edge.h"

class min_heap{
 private:
  std::vector<edge*> edges;
  edge* get_parent(edge*);
  edge* get_child(edge*, char);
  bool is_root(edge*);
  bool is_smaller_than_parent(edge*);
  void swap(edge*, edge*);
  int get_index(edge*);
  bool has_smaller_child(edge*);
  edge* get_min(edge*, edge*);
 public:
  min_heap();
  bool insert(edge*);
  edge* peek();
  edge* pop();
  void print();
  bool is_empty();
};

#endif
