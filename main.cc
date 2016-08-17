/*
 * Tony Tuttle
 * 08/08/2016
 * Homework 2 for the coursera MOOC "C++ for C Programmers"
 *
 * Main Objective:
 * > Implement a Monte Carlo simulation that calculates the average shortest
 * > path in a graph.
 *
 * > The graph should be generated using a pseudorandom number generator to
 * > produce edges and their costs.
 */
#include<iostream>
#include<utility>
#include"random_graph_generator.h"
#include"dijkstra.h"

using namespace std;

double get_avg_distance(map<int, pair<double, int>> dists){
  double inf = numeric_limits<double>::infinity();
  double sum = 0;
  int num_nodes = 0;
  double cur_dist;

  for(int i=1; i<50; ++i){
    cur_dist = dists.find(i)->second.first;
    if(cur_dist < inf){
      sum += cur_dist;
      num_nodes++;
    }
  }
  return num_nodes > 0 ? (sum / num_nodes) : inf;
}

int main(){
  double density = 0.2;
  int node_count = 50;
  pair<double, double> min_max_weight = make_pair(1.0, 10.0);

  // density = 0.2
  random_graph_generator *rgg = new random_graph_generator(density, node_count, min_max_weight);
  graph *g = rgg->create_graph();
  dijkstra *d = new dijkstra(g);
  node *s = g->get_node(0);
  d->find_all_distances(s);
  map<int, pair<double, int>> all_distances = d->get_all_distances();
  // calculate and print avg distance
  double avg_dist = get_avg_distance(all_distances);
  cout << "avg dist for density = 0.2 is " << avg_dist << endl;

  // density = 0.4
  density = 0.4;
  rgg = new random_graph_generator(density, node_count, min_max_weight);
  g = rgg->create_graph();
  d = new dijkstra(g);
  s = g->get_node(0);
  d->find_all_distances(s);
  all_distances = d->get_all_distances();
  // calculate and print avg distance
  avg_dist = get_avg_distance(all_distances);
  cout << "avg dist for density = 0.4 is " << avg_dist << endl;
  
  return 0;
}
