#include <algorithm>
#include <iostream>
#include <vector>

const int cWeightBorder = 1e9;
const int cAbsentEdge = 1e5;

struct Edge {
  int from;
  int too;
  int weight;
};

typedef std::vector<Edge> Graph;

std::vector<int> GetCycle(std::vector<int>& path, int start) {
  std::vector<int> cycle = {start};
  for (int i = path[start]; i != start; i = path[i]) {
    cycle.push_back(i);
  }
  std::reverse(cycle.begin(), cycle.end());
  return cycle;
}

std::vector<int> FordBellman(int number, Graph& graph) {
  std::vector<int> dist(number);
  std::vector<int> path(number, -1);

  for (int i = 0; i < number - 1; ++i) {
    for (auto& [from, too, weight] : graph) {
      if (dist[from] != cWeightBorder && dist[from] + weight < dist[too]) {
        dist[too] = std::max(dist[from] + weight, -cWeightBorder);
        path[too] = from;
      }
    }
  }

  for (auto& [from, too, weight] : graph) {
    if (dist[from] != cWeightBorder && dist[from] + weight < dist[too]) {
      path[too] = from;

      for (int i = 0; i < number - 1; ++i) {
        too = path[too];
      }

      return GetCycle(path, too);
    }
  }

  return {};
}

int main() {
  // input
  Graph graph;
  int number;
  std::cin >> number;
  for (int i = 0; i < number; ++i) {
    for (int j = 0; j < number; ++j) {
      int weight;
      std::cin >> weight;
      if (weight != cAbsentEdge) {
        Edge edge = {i, j, weight};
        graph.push_back(edge);
      }
    }
  }

  // algorithm
  std::vector<int> cycle = FordBellman(number, graph);

  // output
  if (!cycle.empty()) {
    std::cout << "YES\n" << cycle.size() + 1 << '\n';
    for (int u : cycle) {
      std::cout << u + 1 << ' ';
    }
    std::cout << cycle[0] + 1 << '\n';
  } else {
    std::cout << "NO";
  }
}
