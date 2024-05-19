#include <iostream>
#include <vector>

const int cWeightBorder = 2009000999;

struct Edge {
  int from;
  int too;
  int weight;
};

std::vector<int> FordBellman(int vertex, std::vector<Edge>& edge_list,
                             int start_vertex) {
  std::vector<int> dist(vertex, cWeightBorder);
  dist[start_vertex] = 0;

  for (int i = 0; i < vertex - 1; ++i) {
    bool changed = false;
    for (auto& [from, too, weight] : edge_list) {
      if (dist[from] != cWeightBorder && dist[from] + weight < dist[too]) {
        dist[too] = dist[from] + weight;
        changed = true;
      }
    }

    if (!changed) {
      break;
    }
  }

  return dist;
}

int main() {
  // input
  int graph_count;
  std::cin >> graph_count;
  for (int i = 0; i < graph_count; ++i) {
    int vertex;
    int edges;
    std::cin >> vertex >> edges;
    std::vector<Edge> edge_list;
    for (int j = 0; j < edges; ++j) {
      int from;
      int too;
      int weight;
      std::cin >> from >> too >> weight;
      edge_list.push_back({from, too, weight});
      edge_list.push_back({too, from, weight});
    }
    int start_vertex;
    std::cin >> start_vertex;

    // solve
    auto dist = FordBellman(vertex, edge_list, start_vertex);

    // output
    for (int j = 0; j < vertex; ++j) {
      std::cout << dist[j] << ' ';
    }
    std::cout << '\n';
  }
}
