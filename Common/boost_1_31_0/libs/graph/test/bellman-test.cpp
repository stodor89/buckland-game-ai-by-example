// From Louis Lavery <Louis@devilsChimney.co.uk>
/*Expected Output:-
A:   0 A
B:  11 A

Actual Output:-
A:   0 A
B: 2147483647 B
*/

#include <iostream>
#include <iomanip>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/cstdlib.hpp>

int main()
{
  using namespace boost;

  enum { A, B, Z };
  char const name[] = "ABZ";
  int const numVertex = static_cast<int>(Z) + 1;
  typedef std::pair<int,int> Edge;
  Edge edge_array[] = {Edge(B,A)};
  int const numEdges = sizeof(edge_array) / sizeof(Edge);
  int const weight[numEdges] = {11};

  typedef adjacency_list<vecS,vecS,undirectedS,
    no_property,property<edge_weight_t,int> > Graph;

  Graph g(edge_array, edge_array + numEdges, numVertex);

  Graph::edge_iterator ei, ei_end;
  property_map<Graph,edge_weight_t>::type
    weight_pmap = get(edge_weight, g);

  int i = 0;
  for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei, ++i)
    weight_pmap[*ei] = weight[i];

  std::vector<int> parent(numVertex);
  for(i = 0; i < numVertex; ++i)
    parent[i] = i;

  int inf = std::numeric_limits<int>::max();
  std::vector<int> distance(numVertex, inf);
  distance[A] = 0; // Set source distance to zero

  bool const r = bellman_ford_shortest_paths
    (g, int (numVertex),
     weight_map(weight_pmap).distance_map(&distance[0]).
     predecessor_map(&parent[0]));

  if (r) {
    for(int i = 0; i < numVertex; ++i) {
      std::cout << name[i] << ": ";
      if (distance[i] == inf)
        std::cout  << std::setw(3) << "inf";
      else
        std::cout << std::setw(3) << distance[i];
      std::cout << " " << name[parent[i]] << std::endl;
    }
  } else {
    std::cout << "negative cycle" << std::endl;
  }
  return boost::exit_success;
}
