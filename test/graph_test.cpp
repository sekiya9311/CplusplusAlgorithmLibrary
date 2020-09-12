#include <bits/stdc++.h>

#include "../graph/bellman_ford.cpp"
#include "../graph/bipartite_matching.cpp"
#include "../graph/calc_centroids.cpp"
#include "../graph/dijkstraByForAdjacencyMatrix.cpp"
#include "../graph/dijkstra_with_route_count.cpp"
#include "../graph/dinic.cpp"
#include "../graph/ford_fulkerson.cpp"
#include "../graph/heavy_light_decomposition.cpp"
#include "../graph/is_bipartite_graph.cpp"
#include "../graph/lowest_common_ancester.cpp"
#include "../graph/partial_persistence_union_find.cpp"
#include "../graph/strongly_connected_component_decomposition.cpp"
#include "../graph/topological_sort.cpp"
#include "../graph/tree_diameter.cpp"
#include "../graph/two_sat.cpp"
#include "../graph/union_find.cpp"
#include "../graph/warshall_froyd.cpp"

void union_find_test() {
  {
    union_find<> uf(5);
    assert(!uf.same(0, 1));
    assert(uf.size(0) == 1);
    assert(uf.all_size() == 5);
    assert(uf.group_size() == 5);
    assert(uf.edge_count(0) == 0);
    assert(uf.find(0) == 0);
    assert(uf.unite(0, 1));
    assert(uf.same(0, 1));
    assert(!uf.unite(0, 1));
    assert(uf.all_size() == 5);
    assert(uf.group_size() == 4);
    assert(uf.size(0) == uf.size(1));
    assert(uf.size(0) == 2);
    assert(uf.size(2) == 1);
    assert(uf.find(1) == 0);
    assert(uf.unite(2, 0));
    assert(!uf.unite(1, 2));
    assert(uf.edge_count(0) == uf.edge_count(2));
    assert(uf.edge_count(0) == 4);
  }
  {
    std::vector<long long> weights(5);
    std::iota(begin(weights), end(weights), 1);
    union_find<long long> uf(weights);
    assert(uf.weight(0) == 1);
    uf.unite(0, 1);
    assert(uf.weight(0) == 3);
  }
}

void graph_test() { union_find_test(); }