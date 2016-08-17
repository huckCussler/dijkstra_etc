/*
 * Creates a random graph based on the graphs density (how likely any possible edge is to exist
 * in the graph), the number of nodes in the graph, and the possible range of weights for each
 * edge.
 */
#include"random_graph_generator.h"

random_graph_generator::
random_graph_generator(double d, int nc, std::pair<double, double> wr):
density(d), node_count(nc){
  srand(time(NULL));
  if(wr.first > wr.second){
    double tmp = wr.first;
    wr.first = wr.second;
    wr.second = tmp;
  }
  weight_range = wr;
}

void random_graph_generator::print(){
  std::cout << "density: " << density << "\nnode_count: " << node_count;
  std::cout << "\nweight_range: " << weight_range.first << " to ";
  std::cout << std::get<1>(weight_range) << std::endl;
}

graph *random_graph_generator::create_graph(){
  graph *g = new graph();
  // create/add nodes
  for(int i=0; i<node_count; ++i)
    if(!g->add_node(new node(i)))
      std::cout << "\nunable to add new node" << std::endl;
  // create/add edges
  for(int i=0; i<node_count-1; ++i)
    for(int j=i+1; j<node_count; ++j)
      if(should_add_edge())
	g->add_edge(new edge(std::make_pair(g->get_nodes()[i], g->get_nodes()[j]),
			     make_weight()));
  return g;
}

bool random_graph_generator::should_add_edge(){
  return static_cast<double>(rand()) / RAND_MAX < density;
}

double random_graph_generator::make_weight(){
  double d = static_cast<double>(rand()) / RAND_MAX;
  return weight_range.first + d * (weight_range.second - 1);
}
