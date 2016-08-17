/*
 * Tony Tuttle
 * 08/16/2016
 *
 * A node is represented by its id (int).  For each node we keep a vector of its neighbors.
 */
#include"node.h"

node::node(const int n):id(n){
  adj_list = {};
}

int node::get_id(){return id;}

std::vector<node*> node::get_neighbors(){ return adj_list; }

bool node::add_neighbor(node *n){
  if(n->id == id)
    return false;

  int to_add = n->get_id();
  std::vector<node*>::iterator it;
  for(it = adj_list.begin(); it != adj_list.end(); ++it){
    if(to_add < (*it)->id)
      return reciprocal_add(it, n);
    else if(to_add == (*it)->id) // it's already in adj_list
      return false;
  }
  if(it == adj_list.end()) // it's the new largets element in adj_list
    return reciprocal_add(it, n);
  return false;
}

bool node::reciprocal_add(const std::vector<node*>::iterator it, node *n){
  adj_list.insert(it, n);
  n->add_neighbor(this);
  return true;
}

bool node::operator<(node rhs){
  return id < rhs.get_id();
}

bool node::operator==(node rhs){
  return id == rhs.get_id();
}

void node::print(){
  std::cout << id << ": ( ";
  for(node *al : adj_list)
    std::cout << al->get_id() << " ";
  std::cout << ")" << std::endl;
}
