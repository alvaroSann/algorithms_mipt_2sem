#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

const long long cInf = 1e18;

struct Edge {
  int to;
  long long capacity;
  long long cost;
  int rev;
};

std::vector<std::vector<Edge>> graph;
std::vector<long long> dist;
std::vector<int> prev_v, prev_e;

void AddEdge(int from, int to, long long capacity, long long cost) {
  graph[from].push_back(
      {to, capacity, cost, static_cast<int>(graph[to].size())});
  graph[to].push_back(
      {from, 0, -cost, static_cast<int>(graph[from].size()) - 1});
}

static std::pair<long long, long long> Mcmf(int source, int sink) {
  int n = graph.size();
  long long flow = 0;
  long long min_cost = 0;

  while (true) {
    std::fill(dist.begin(), dist.end(), cInf);
    dist[source] = 0;
    bool update = true;

    while (update) {
      update = false;

      for (int v = 0; v < n; ++v) {
        if (dist[v] == cInf) {
          continue;
        }

        for (int i = 0; i < static_cast<int>(graph[v].size()); ++i) {
          Edge& e = graph[v][i];
          if (e.capacity > 0 && dist[e.to] > dist[v] + e.cost) {
            dist[e.to] = dist[v] + e.cost;
            prev_v[e.to] = v;
            prev_e[e.to] = i;
            update = true;
          }
        }
      }
    }

    if (dist[sink] == cInf) {
      break;
    }

    long long d = cInf;

    for (int v = sink; v != source; v = prev_v[v]) {
      d = std::min(d, graph[prev_v[v]][prev_e[v]].capacity);
    }

    flow += d;
    min_cost += d * dist[sink];

    for (int v = sink; v != source; v = prev_v[v]) {
      Edge& e = graph[prev_v[v]][prev_e[v]];
      e.capacity -= d;
      graph[v][e.rev].capacity += d;
    }
  }
  return {flow, min_cost};
}

int main() {
  // input
  int n;
  int m;
  std::cin >> n >> m;
  graph.resize(n + 1);
  dist.resize(n + 1);
  prev_v.resize(n + 1);
  prev_e.resize(n + 1);
  for (int i = 0; i < m; ++i) {
    int from;
    int to;
    long long capacity;
    long long cost;
    std::cin >> from >> to >> capacity >> cost;
    AddEdge(from, to, capacity, cost);
  }

  // algorithm
  std::pair<long long, long long> result = Mcmf(1, n);

  // output
  std::cout << result.second;
}
