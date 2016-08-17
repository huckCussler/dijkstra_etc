/*
 * Tony Tuttle
 * 08/16/2016
 *
 * A graph is a vector of nodes and a vector of edges.
 */
#include"graph.h"

graph::graph(){
  nodes = {}; //new std::vector<node>();
  edges = {}; //new std::vector<edge>();
}

bool graph::add_node(node *n){
  std::vector<node*>::iterator it;

  for(it = nodes.begin(); it != nodes.end(); ++it){
    if(*n < (**it))
      return add_node_helper(it, n);
    else if(n == (*it))
      return false;
  }
  return add_node_helper(it, n);
}

bool graph::add_node_helper(const std::vector<node*>::iterator it, node *n){
  nodes.insert(it, n);
  return true;
}

edge* graph::get_edge(int l_id, int r_id){
  if(l_id > r_id){
    int tmp = l_id;
    l_id = r_id;
    r_id = tmp;
  }
  for(edge *e : edges)
    if(e->get_nodes().first->get_id() == l_id && e->get_nodes().second->get_id() == r_id)
      return e;
  throw std::invalid_argument("edge with given node id's is not in the graph");
}

// Edges will be sorted first by the id of the first node, secondly by the id
// of the second node.
// e.g. edges = {(0,1), (1,2), (1,4), (2,3), (2,6), ... }
// TODO : combine add_edge and add_node to one method
//      : probably in a graph_utils class
bool graph::add_edge(edge *e){
  if(!(contains_node(e->get_nodes().first) || contains_node(e->get_nodes().second)))
    return false;

  std::vector<edge*>::iterator it;

  for(it = edges.begin(); it != edges.end(); ++it){
    if(*e < (**it))
      return add_edge_helper(it, e);
    else if(*e == (**it))
      return false;
  }
  return add_edge_helper(it, e);
}

bool graph::add_edge_helper(const std::vector<edge*>::iterator it, edge *e){
  e->get_nodes().first->add_neighbor(e->get_nodes().second);
  edges.insert(it, e);
  return true;
}

std::vector<node*> graph::get_nodes(){ return nodes; }

std::vector<edge*> graph::get_edges(){ return edges; }

bool graph::contains_node(node *n2){
  for(node *n : nodes)
    if(n == n2)
      return true;
  return false;
}

node* graph::get_node(int x){
  for(node *n : nodes)
    if(n->get_id() == x)
      return n;
  throw std::invalid_argument("attempted to get a node not in the graph");
}

void graph::print(){
  std::cout << "\nNodes:" << std::endl;
  for(node *n : nodes){
    std::cout << "\t";
    n->print();
  }

  std::cout << "Edges:" << std::endl;
  for(edge *e : edges){
    std::cout << "\t";
    e->print();
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void graph::create_dot_file(){
  
}
