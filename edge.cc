/*
 * Tony Tuttle
 * 08/16/2016
 *
 * An edge is a pair of nodes and a weight.
 */

#include"edge.h"

// edges must be in the form (a,b) where a<b
edge::edge(std::pair<node*, node*> ens, const double wt):nodes(ens), weight(wt){
  if(nodes.first->get_id() == nodes.second->get_id())
    throw std::invalid_argument("node id's for an edge must be different");
  if(wt < 1.0)
    throw std::invalid_argument("edges must have weight >= 1");
  if(nodes.second->get_id() < nodes.first->get_id())
    swap_nodes();
}

void edge::swap_nodes(){
  node *tmp = nodes.first;
  nodes.first = nodes.second;
  nodes.second = tmp;
}

std::pair<node*, node*> edge::get_nodes(){ return nodes; }

double edge::get_weight(){ return weight; }

bool edge::operator==(edge rhs){
  return (nodes.first->get_id() == rhs.get_nodes().first->get_id()) && 
    (nodes.second->get_id() == rhs.get_nodes().second->get_id());
}

bool edge::operator<(edge rhs){
  int nf = nodes.first->get_id();
  int rnf = rhs.get_nodes().first->get_id();
  return nf < rnf || (nf == rnf && nodes.second->get_id() < rhs.get_nodes().second->get_id()); 
}

void edge::print(){
  std::cout << "((" << nodes.first->get_id() << "," << nodes.second->get_id();
  std::cout << "), " << weight << ")";
}
