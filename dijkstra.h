#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include<map>
#include<limits>
#include<algorithm>
#include"graph.h"
#include"min_heap.h"
#include"node.h"

class dijkstra{
 private:
  graph *g;
  min_heap *mh;
  std::vector<node*> unvisited;
  std::vector<node*> visited;
  node* get_unvisited(edge*);
  bool is_unvisited(node*);
  std::map<int, std::pair<double, int>> all_distances;
 public:
  dijkstra(graph*);
  void find_all_distances(node*);
  void print_all_distances();
  std::map<int, std::pair<double, int>> get_all_distances();
};

#endif
