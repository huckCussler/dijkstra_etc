/*
 * Tony Tuttle
 * 08/16/2016
 *
 * Given an undirected, weighted graph g with all positive edge weights and a starting node s in g,
 * calculates the distance from s to all other nodes in g.  Additionally, it saves the previous
 * node for each calculated distance, making it possible to trace a shortest path back to s.
 *
 * If a node is disconnected from s, then the distance will be infinity and its previous node will
 * be -1.
 *
 * The distance to s will always be 0 and its previous node will be -1.
 */
#include"dijkstra.h"

dijkstra::dijkstra(graph *gr) : g(gr){
  mh = new min_heap();
}

/*
 * 's' is the start node.
 * Returns a map<int, pair<double, int> where the key <int> is the id of the destination node.
 * The value is a pair<double, int> where
 *   the double is the total distance from s to the destination, and
 *   the int is destination's previous node in the shortest path.
 */
void dijkstra::find_all_distances(node *s){
  double inf = std::numeric_limits<double>::infinity();

  for(node *n : g->get_nodes()){
    all_distances.insert(std::make_pair(n->get_id(), std::make_pair((n==s ? 0.0 : inf), -1)));
    if(n != s)
      unvisited.push_back(n);
  }
   
  visited.push_back(s);

  // for each neighbor of s
  for(node *n : s->get_neighbors()){
    // if neighbor in unvisited
    if(std::find(unvisited.begin(), unvisited.end(), n) != unvisited.end()){
      // insert edge(s, neighbor) into mh
      int s_id = s->get_id();
      int n_id = n->get_id();
      edge *e = g->get_edge(s_id, n_id);
      mh->insert(e);
      // if dist to s + edge weight from s to n < n's tentative dist
      double new_wt = all_distances[s_id].first + e->get_weight();
      if(new_wt < all_distances[n_id].first){
	all_distances[n_id].first = new_wt;
	all_distances[n_id].second = s_id;
      }
    }
  }

  while(!mh->is_empty()){
    edge *cur_edge = mh->pop();
    node *cur_node = get_unvisited(cur_edge); // edge will have one visited, one unvisited node
    for(node *n : cur_node->get_neighbors()){
      if(std::find(unvisited.begin(), unvisited.end(), n) != unvisited.end()){
	int cur_node_id = cur_node->get_id();
	int n_id = n->get_id();
	edge *e = g->get_edge(cur_node_id, n_id);
	mh->insert(e);
	double new_wt = all_distances[cur_node_id].first + e->get_weight();
	if(new_wt < all_distances[n_id].first){
	  all_distances[n_id].first = new_wt;
	  all_distances[n_id].second = cur_node_id;
	}
      }
    }
    // remove current from unvisited and put into visited
    unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), cur_node), unvisited.end());
    visited.push_back(cur_node);
  }
}

bool dijkstra::is_unvisited(node *n){
  return std::find(unvisited.begin(), unvisited.end(), n) != unvisited.end();
}

node* dijkstra::get_unvisited(edge *e){
  node *f = e->get_nodes().first;
  return is_unvisited(f) ? f : e->get_nodes().second;
}

std::map<int, std::pair<double, int>> dijkstra::get_all_distances(){
  return all_distances;
}

void dijkstra::print_all_distances(){
  for(std::pair<int, std::pair<double, int>> d : all_distances){
    std::cout << "node " << d.first << ", dist = " << d.second.first;
    std::cout << ", prev =  " << d.second.second << std::endl;
  }
}
