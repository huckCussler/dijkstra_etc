#include<iostream>
#include<cassert>
#include<algorithm>
#include<vector>
#include"random_graph_generator.h"
#include"node.h"
#include"min_heap.h"
#include"dijkstra.h"

using namespace std;

void test_node(){
  node *n = new node(0);
  assert(n->get_id() == 0);            // setting id works
  assert(n->get_neighbors().empty());  // no neighbors by default
  assert(n->add_neighbor(n) == false); // cannot add itself as a neighbor
  
  node *n2 = new node(1);
  assert(n2->get_id() == 1);           // setting id works
  assert(n2->get_neighbors().empty()); // no neighbors by default
  assert(n2->add_neighbor(n) == true); // adding a valid neighbor works
  vector<node*> n2_n = n2->get_neighbors();
  vector<node*>::iterator n2_it = find(n2_n.begin(), n2_n.end(), n);
  assert(n2_it != n2_n.end());         // neighbors is not empty
  
  vector<node*> n_n = n->get_neighbors();
  vector<node*>::iterator n_it = find(n_n.begin(), n_n.end(), n2);
  assert(n_it != n_n.end()); // reciprocal add worked

  for(int i=2; i<10; i+=2)
    n->add_neighbor(new node(i));

  for(int i=3; i<13; i+=2)
    n->add_neighbor(new node(i));

  assert(*n < *n2);

  // sanity checks
  /*
  n->print();
  n2->print();
  */
  cout << "\nall tests passed in test_node()" << endl;
}

void test_edge(){
  node *n0 = new node(0);
  node *n1 = new node(1);
  edge *e0 = new edge(make_pair(n0, n1), 1.0);
  pair<node*, node*> e0_n = e0->get_nodes();
  assert(e0_n.first->get_id() == 0);  // first node should be 0
  assert(e0_n.second->get_id() == 1); // second node should be 1
  assert(e0->get_weight() == 1.0);    // weight is correct

  node *n2 = new node(2);
  edge *e1 = new edge(make_pair(n2, n1), 2.0);
  pair<node*, node*> e1_n = e1->get_nodes();
  assert(e1_n.first->get_id() == 1);  // first node should be 1
  assert(e1_n.second->get_id() == 2); // second node should be 2
  assert(e1->get_weight() == 2.0);    // weight is correct
  assert(*e0 < *e1);                  // test < operator

  edge *e2 = new edge(make_pair(n1, n0), 1.0);
  assert(*e0 == *e2); // test == operator

  // sanity checks
  /*
  cout << endl;
  e0->print();
  cout << endl;
  e1->print();
  cout << endl;
  e2->print();
  cout << endl;
  */

  cout << "\nall tests passed in test_edge()" << endl;
}

void test_graph(){
  graph *g0 = new graph();
  assert(g0->get_nodes().empty()); // no nodes
  assert(g0->get_edges().empty()); // no edges
  
  node *n0 = new node(0);
  node *n1 = new node(1);
  edge *e0 = new edge(make_pair(n0, n1), 1.0);
  bool e_added = g0->add_edge(e0);
  assert(!e_added); // can't add edge if nodes not in graph

  bool n_added = g0->add_node(n0);
  assert(n_added);  // node successfully added
  n_added = g0->add_node(n0);
  assert(!n_added); // can't add node already in graph
  
  n_added = g0->add_node(n1);
  assert(n_added); // can add new node

  e_added = g0->add_edge(e0);
  assert(e_added); // should work this time

  e_added = g0->add_edge(e0);
  assert(!e_added); // edge already exists

  node *n2 = new node(2);
  node *n4 = new node(4);
  node *n8 = new node(8);
  g0->add_node(n2);
  g0->add_node(n4);
  g0->add_node(n8);

  edge *e1 = new edge(make_pair(n0, n4), 2.0);
  g0->add_edge(e1);
  edge *e2 = new edge(make_pair(n0, n2), 3.0);
  g0->add_edge(e2);
  

  // sanity check
  //g0->print();
  
  cout << "\nall tests passed in test_graph()" << endl;
}

void test_rgg(){
  random_graph_generator *rgg = new 
    random_graph_generator(0.2, 4, make_pair<double, double>(10.0, 1.0));
  graph *g = rgg->create_graph();
  
  // sanity check
  g->print();

  dijkstra *d = new dijkstra(g);
  // get the node with id = 0 from g
  node *s = g->get_node(0);
  // call find_all_distances with that node as arg
  d->find_all_distances(s);
  d->print_all_distances();

  cout << "\nall tests passed in test_rgg()" << endl;
}

void test_minheap(){
  min_heap *mh = new min_heap();

  assert(mh->peek() == nullptr); // empty heap => root is nullptr
  assert(mh->pop() == nullptr);  // pop from empty heap

  node *n0 = new node(0);
  node *n1 = new node(1);
  edge *e2 = new edge(make_pair(n0, n1), 2.0);
  assert(mh->insert(e2));   // add edge to empty heap
  assert(!mh->insert(e2));  // can't add edge already in heap
  assert(mh->peek() == e2); // e2 is root
  assert(mh->pop() == e2);  // pop from a heap with one item
  assert(mh->insert(e2));

  node *n2 = new node(2);
  edge *e1 = new edge(make_pair(n0, n2), 1.0);
  assert(mh->insert(e1));   // add edge to heap with another edge
  assert(!mh->insert(e1));  // can't add edge already in heap
  assert(mh->peek() == e1); // e1 is root

  node *n3 = new node(3);
  edge *e3 = new edge(make_pair(n1, n3), 3.0);
  assert(mh->insert(e3));   // new edge at bottom
  node *n4 = new node(4);
  edge *e1_5 = new edge(make_pair(n1, n4), 1.5);
  assert(mh->insert(e1_5)); // new edge in middle
  assert(mh->peek() == e1); // e1 is root (still)

  edge *e4 = new edge(make_pair(n0, n3), 4.0);
  assert(mh->insert(e4));
  edge *e3b = new edge(make_pair(n0, n4), 3.0);
  assert(mh->insert(e3b));

  assert(mh->pop() == e1); // test pop
  assert(mh->insert(e1));

  // sanity check
  //mh->print();
  
  cout << "\nall tests passed in test_minheap()" << endl;
}

int main(){
  test_node();
  test_edge();
  test_graph();
  test_rgg();
  test_minheap();

  cout << "\nexiting main in tester\n" << endl;
  return 0;
}
