#include <algorithm>
#include <iostream>
#include <vector>

class DSU {
 private:
  std::vector<int> parent_;
  std::vector<int> rank_;

 public:
  DSU(int size) {
    parent_.resize(size);
    rank_.resize(size);

    for (int i = 0; i < size; ++i) {
      parent_[i] = i;
      rank_[i] = 0;
    }
  }

  int Find(int node_number) {
    if (node_number == parent_[node_number]) {
      return node_number;
    }

    return parent_[node_number] = Find(parent_[node_number]);
  }

  void Union(int from, int to) {
    from = Find(from);
    to = Find(to);

    if (rank_[from] < rank_[to]) {
      std::swap(from, to);
    }

    parent_[to] = from;

    if (rank_[from] == rank_[to]) {
      ++rank_[from];
    }
  }
};

class Edge {
 public:
  int from;
  int to;
  int weight;

  Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

class Graph {
 private:
  static bool Comp(const Edge& a, const Edge& b) { return a.weight < b.weight; }

 public:
  int vertex;
  int edges;
  std::vector<Edge> edges_list;

  Graph(int vertex, int edges) : vertex(vertex), edges(edges) {}

  void Kruskal() {
    DSU dsu(vertex);
    std::sort(edges_list.begin(), edges_list.end(), Comp);
    int edge_counter = 0;
    int iter = 0;
    int sum = 0;

    while (edge_counter < vertex - 1) {
      Edge edge = edges_list[iter++];

      int first = dsu.Find(edge.from);
      int second = dsu.Find(edge.to);

      if (first != second) {
        sum += edge.weight;
        dsu.Union(first, second);
        ++edge_counter;
      }
    }

    std::cout << sum;
  }
};

int main() {
  // input
  int vertex;
  int edges;
  std::cin >> vertex >> edges;

  Graph graph(vertex, edges);

  for (int i = 0; i < edges; ++i) {
    int from;
    int to;
    int weight;
    std::cin >> from >> to >> weight;
    graph.edges_list.push_back(Edge(from - 1, to - 1, weight));
  }

  // algorithm and output
  graph.Kruskal();
}
