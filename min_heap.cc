/*
 * Tony Tuttle
 * 08/16/2016
 *
 * A min heap of edge objects.  The smallest edge (by weight) will always be the root node
 * (at index 1) of the heap.  For each node in the heap, it is guaranteed that the weight of
 * the node will be <= the weight of both of its children.
 */
#include"min_heap.h"

min_heap::min_heap(){
  edges.push_back(nullptr); // burn index 0
}

edge* min_heap::get_parent(edge *e){
  if(is_root(e))
    return nullptr;
  return edges[get_index(e) / 2];
}

bool min_heap::is_empty(){
  return edges.size() <= 1;
}

int min_heap::get_index(edge *e){
  std::vector<edge*>::iterator it = std::find(edges.begin(), edges.end(), e);
  if(it == edges.end())
    throw std::invalid_argument("edge not in min heap");
  return it - edges.begin();
}

bool min_heap::insert(edge *e){
  if(std::find(edges.begin(), edges.end(), e) != edges.end())
    return false;

  edges.push_back(e);

  while((!is_root(e)) && is_smaller_than_parent(e))
    swap(e, get_parent(e));
  return true;
}

edge* min_heap::peek(){
  if(edges.size() <= 1)
    return nullptr;
  return edges[1];
}

void min_heap::swap(edge *e, edge *other){
  int other_idx = get_index(other);
  edges[get_index(e)] = other;
  edges[other_idx] = e;
}

edge* min_heap::pop(){
  if(edges.size() <= 1)
    return nullptr;
  
  edge *to_ret = edges[1];

  // get last item in edges and put it at edges[1]
  // TODO : this breaks if heap will be empty after pop
  edges[1] = edges.back();
  edges.pop_back();
  if(edges.size() == 1)
    return to_ret;

  edge *e = edges[1];

  // percolate it down until it's smaller than both its children
  while(has_smaller_child(e)){
    edge *rc = get_child(e, 'r');
    edge *lc = get_child(e, 'l');
    if(rc == nullptr)
      swap(e, lc);
    else
      swap(e, get_min(lc, rc));
  }
  return to_ret;
}

bool min_heap::has_smaller_child(edge *e){
  edge *l = get_child(e, 'l');
  if(l == nullptr) // e is a leaf
    return false;

  edge *r = get_child(e, 'r');
  if(r == nullptr) // e has only a left child
    return is_smaller_than_parent(l);

  return is_smaller_than_parent(get_min(l, r));
}

edge* min_heap::get_min(edge *e1, edge *e2){
  return e1->get_weight() < e2->get_weight() ? e1 : e2;
}

edge* min_heap::get_child(edge *e, char c){
  if(c == 'l'){
    unsigned int l_ind = get_index(e) * 2;
    if(l_ind < edges.size())
      return edges[l_ind];
  }
  if(c == 'r'){
    unsigned int r_ind = get_index(e) * 2 + 1;
    if(r_ind < edges.size())
      return edges[r_ind];
  }
  return nullptr;
}

bool min_heap::is_smaller_than_parent(edge *e){
  return e->get_weight() < get_parent(e)->get_weight();
}

bool min_heap::is_root(edge *e){
  return edges[1] == e;
}

void min_heap::print(){
  unsigned int next_level_idx = 2;

  std::cout << std::endl;
  for(unsigned int i=1; i<edges.size(); ++i){
    if(i == next_level_idx){
      std::cout << std::endl;
      next_level_idx *= 2;
    }
    edges[i]->print();
    std::cout << "\t";
  }
}
