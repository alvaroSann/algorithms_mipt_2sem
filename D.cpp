#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 public:
  Graph(int vertex) {
    graph_.resize(vertex);
    reversed_graph_.resize(vertex);
  }

  void AddEdge(int from, int too) {
    graph_[from].push_back(too);
    reversed_graph_[too].push_back(from);
  }

  std::vector<int> FindScc() {
    visited_.assign(graph_.size(), 0);
    for (int i = 0; i < static_cast<int>(graph_.size()); ++i) {
      if (!static_cast<bool>(visited_[i])) {
        DfsForTopSort(i);
      }
    }
    std::reverse(order_.begin(), order_.end());

    visited_.assign(graph_.size(), 0);
    int component = 0;
    for (int vertex : order_) {
      if (!static_cast<bool>(visited_[vertex])) {
        DfsForScc(vertex, ++component);
      }
    }

    return visited_;
  }

 private:
  std::vector<std::vector<int>> graph_;
  std::vector<std::vector<int>> reversed_graph_;
  std::vector<int> visited_;
  std::vector<int> order_;

  void DfsForTopSort(int vertex) {
    visited_[vertex] = 1;
    for (int too : reversed_graph_[vertex]) {
      if (!static_cast<bool>(visited_[too])) {
        DfsForTopSort(too);
      }
    }
    order_.push_back(vertex);
  }

  void DfsForScc(int vertex, int component) {
    visited_[vertex] = component;
    for (int too : graph_[vertex]) {
      if (!static_cast<bool>(visited_[too])) {
        DfsForScc(too, component);
      }
    }
  }
};

int main() {
  // input
  int vertex;
  int edge;
  std::cin >> vertex >> edge;
  Graph graph(vertex);

  for (int i = 0; i < edge; ++i) {
    int from;
    int too;
    std::cin >> from >> too;
    if (from != too) {
      graph.AddEdge(from - 1, too - 1);
    }
  }

  // algorithm
  int scc_count = 0;
  std::vector<int> strongly_connected_components = graph.FindScc();
  for (int color : strongly_connected_components) {
    scc_count = std::max(scc_count, color);
  }

  // output
  std::cout << scc_count << '\n';
  for (int color : strongly_connected_components) {
    std::cout << scc_count - color + 1 << ' ';
  }
}
