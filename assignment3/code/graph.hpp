#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

// an unweighted directed Graph whose vertex properties (e.g. int, Color,
// std::pair<int, Color>, etc.) can be passed as template parameter
// for simplicity vertices can only be added, but not removed
template <typename VertexProp>
class Graph {
 public:
  // builds an empty graph
  Graph() = default;

  // builds a graph with num_vertices unconnected vertices
  explicit Graph(std::size_t num_vertices);

  // adds a vertex and returns its index
  std::size_t add_vertex(VertexProp&& prop);

  // creates and edge between two vertices and returns if the creation was
  // successful (e.g. the edge could already exist)
  bool add_edge(const std::size_t v_idx1, const std::size_t v_idx2);

  // removes an edge between two vertices and returns if the removal was
  // successful
  bool remove_edge(const std::size_t v_idx1, const std::size_t v_idx2);

  // returns the neighbors of a vertex
  const std::list<std::size_t>& get_neighbors(const std::size_t v_idx) const;

  // reserves space for size number of vertices
  void reserve(const std::size_t size);

  // returns if there is an edge between v_idx1 and v_idx2
  bool has_edge(const std::size_t v_idx1, const std::size_t v_idx2) const;

  // returns the properties for a given vertex index
  VertexProp& get_vertex(const std::size_t v_idx);
  const VertexProp& get_vertex(const std::size_t v_idx) const;

  // returns the number of vertices
  std::size_t num_vertices() const;

  // returns the number of edges
  std::size_t num_edges() const;

  // returns the capacity
  std::size_t capacity() const;

 private:
  // stores the neighbors of each vertex
  std::vector<std::list<std::size_t>> adj_list_;
  // stores the vertex properties
  std::vector<VertexProp> vertex_props_;
};

#endif  // GRAPH_HPP
