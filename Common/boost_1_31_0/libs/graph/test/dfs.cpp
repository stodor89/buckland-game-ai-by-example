//=======================================================================
// Copyright 2001 University of Notre Dame.
// Author: Jeremy G. Siek
//
// This file is part of the Boost Graph Library
//
// You should have received a copy of the License Agreement for the
// Boost Graph Library along with the software; see the file LICENSE.
// If not, contact Office of Research, University of Notre Dame, Notre
// Dame, IN 46556.
//
// Permission to modify the code and to distribute modified code is
// granted, provided the text of this NOTICE is retained, a notice that
// the code was modified is included with the above COPYRIGHT NOTICE and
// with the COPYRIGHT NOTICE in the LICENSE file, and that the LICENSE
// file is distributed with the modified code.
//
// LICENSOR MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.
// By way of example, but not limitation, Licensor MAKES NO
// REPRESENTATIONS OR WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY
// PARTICULAR PURPOSE OR THAT THE USE OF THE LICENSED SOFTWARE COMPONENTS
// OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS, COPYRIGHTS, TRADEMARKS
// OR OTHER RIGHTS.
//=======================================================================

#include <boost/config.hpp>
#include <boost/test/test_tools.hpp>
#include <stdlib.h>

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_archetypes.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/random.hpp>

#include <boost/random/mersenne_twister.hpp>

template <typename ColorMap, typename ParentMap,
  typename DiscoverTimeMap, typename FinishTimeMap>
class dfs_test_visitor {
  typedef typename boost::property_traits<ColorMap>::value_type ColorValue;
  typedef typename boost::color_traits<ColorValue> Color;
public:
  dfs_test_visitor(ColorMap color, ParentMap p, DiscoverTimeMap d,
                   FinishTimeMap f)
    : m_color(color), m_parent(p), 
    m_discover_time(d), m_finish_time(f), m_time(0) { }
  
  template <class Vertex, class Graph>
  void initialize_vertex(Vertex u, Graph& g) {
    BOOST_TEST( boost::get(m_color, u) == Color::white() );
  }
  template <class Vertex, class Graph>
  void start_vertex(Vertex u, Graph& g) {
    BOOST_TEST( boost::get(m_color, u) == Color::white() );
  }
  template <class Vertex, class Graph>
  void discover_vertex(Vertex u, Graph& g) {
    using namespace boost;
    BOOST_TEST( get(m_color, u) == Color::gray() );
    BOOST_TEST( get(m_color, get(m_parent, u)) == Color::gray() );

    put(m_discover_time, u, m_time++);
  }
  template <class Edge, class Graph>
  void examine_edge(Edge e, Graph& g) {
    using namespace boost;
    BOOST_TEST( get(m_color, source(e, g)) == Color::gray() );
  }
  template <class Edge, class Graph>
  void tree_edge(Edge e, Graph& g) {
    using namespace boost;
    BOOST_TEST( get(m_color, target(e, g)) == Color::white() );
    
    put(m_parent, target(e, g), source(e, g));
  }
  template <class Edge, class Graph>
  void back_edge(Edge e, Graph& g) {
    using namespace boost;
    BOOST_TEST( get(m_color, target(e, g)) == Color::gray() );
  }
  template <class Edge, class Graph>
  void forward_or_cross_edge(Edge e, Graph& g) {
    using namespace boost;
    BOOST_TEST( get(m_color, target(e, g)) == Color::black() );
  }
  template <class Vertex, class Graph>
  void finish_vertex(Vertex u, Graph& g) {
    using namespace boost;
    BOOST_TEST( get(m_color, u) == Color::black() );
    
    put(m_finish_time, u, m_time++);
  }
private:
  ColorMap m_color;
  ParentMap m_parent;
  DiscoverTimeMap m_discover_time;
  FinishTimeMap m_finish_time;
  typename boost::property_traits<DiscoverTimeMap>::value_type m_time;
};

template <typename Graph>
struct dfs_test
{
  typedef boost::graph_traits<Graph> Traits;
  typedef typename Traits::vertices_size_type
    vertices_size_type;

  static void go(vertices_size_type max_V) {
    using namespace boost;
    typedef typename Traits::vertex_descriptor vertex_descriptor;
    typedef typename boost::property_map<Graph, 
      boost::vertex_color_t>::type ColorMap;
    typedef typename boost::property_traits<ColorMap>::value_type ColorValue;
    typedef typename boost::color_traits<ColorValue> Color;

    vertices_size_type i, k;
    typename Traits::edges_size_type j;
    typename Traits::vertex_iterator vi, vi_end, ui, ui_end;

    boost::mt19937 gen;

    for (i = 0; i < max_V; ++i)
      for (j = 0; j < i*i; ++j) {
        Graph g;
        generate_random_graph(g, i, j, gen);

        ColorMap color = get(boost::vertex_color, g);
        std::vector<vertex_descriptor> parent(num_vertices(g));
        for (k = 0; k < num_vertices(g); ++k)
          parent[k] = k;
        std::vector<int> discover_time(num_vertices(g)),
          finish_time(num_vertices(g));

        dfs_test_visitor<ColorMap, vertex_descriptor*,
          int*, int*> vis(color, &parent[0], 
                          &discover_time[0], &finish_time[0]);

        boost::depth_first_search(g, visitor(vis).color_map(color));

        // all vertices should be black
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
          BOOST_TEST(get(color, *vi) == Color::black());

        // check parenthesis structure of discover/finish times
        // See CLR p.480
        for (boost::tie(ui, ui_end) = vertices(g); ui != ui_end; ++ui)
          for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
            vertex_descriptor u = *ui, v = *vi;
            if (u != v) {
              BOOST_TEST( finish_time[u] < discover_time[v]
                          || finish_time[v] < discover_time[u]
                          || (discover_time[v] < discover_time[u]
                               && finish_time[u] < finish_time[v]
                               && boost::is_descendant(u, v, &parent[0]))
                          || (discover_time[u] < discover_time[v]
                               && finish_time[v] < finish_time[u]
                               && boost::is_descendant(v, u, &parent[0]))
                        );
            }
          }
      }

  }
};


// usage: dfs.exe [max-vertices=15]

int test_main(int argc, char* argv[])
{
  int max_V = 15;
  if (argc > 1)
    max_V = atoi(argv[1]);

  // Test directed graphs.
  dfs_test< boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
           boost::property<boost::vertex_color_t, boost::default_color_type> > 
    >::go(max_V);
  // Test undirected graphs.
  dfs_test< boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
           boost::property<boost::vertex_color_t, boost::default_color_type> >
    >::go(max_V);

  return 0;
}

