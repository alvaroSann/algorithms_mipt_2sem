#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  int s_vertex;
  int s_order;

  explicit Edge(int vertex = 0, int order = 0)
      : s_vertex(vertex), s_order(order) {}
};

struct Bridge {
  int s_from, s_to, sb_order;

  explicit Bridge(int from = 0, int too = 0, int order = 0)
      : s_from(from), s_to(too), sb_order(order) {}

  bool operator<(const Bridge& other) const {
    return std::tie(s_from, s_to, sb_order) <
           std::tie(other.s_from, other.s_to, other.sb_order);
  }
};

class Graph {
 public:
  Graph(int vertex, int edge)
      : vertex_(vertex),
        edge_(edge),
        colors_(vertex + 1, 0),
        tin_(vertex + 1, -1),
        tout_(vertex + 1, -1),
        bridges_(edge + 1, 0),
        edges_(vertex + 1) {}

  // Add one direct edge
  void AddOneDirectEdge(int from, int too, int order) {
    bridge_edge_.emplace_back(from < too ? from : too, from < too ? too : from,
                              order);
  }

  // Output
  std::tuple<int, int, std::vector<int>> Result() {  // Rust moment
    // As precaution, we delete all multi-edges
    DeleteMultiEdge();
    // General part of solve algorithm
    DFS();
    return {bridge_, edge_, bridges_};
  }

 private:
  int vertex_ = 0;
  int edge_ = 0;
  int bridge_ = 0;
  int time_ = 0;
  std::vector<int> colors_;
  std::vector<int> tin_;
  std::vector<int> tout_;
  std::vector<int> bridges_;
  std::vector<std::vector<Edge>> edges_;
  std::vector<Bridge> bridge_edge_;

  // Dfs algorithm
  void DfsProcess(int parent, int vertex) {
    colors_[vertex] = 1;
    tin_[vertex] = time_;
    ++time_;
    tout_[vertex] = tin_[vertex];
    for (const auto& adj_vertex : edges_[vertex]) {
      if (adj_vertex.s_vertex != parent) {
        if (colors_[adj_vertex.s_vertex] == 0) {
          DfsProcess(vertex, adj_vertex.s_vertex);
          tout_[vertex] = std::min(tout_[vertex], tout_[adj_vertex.s_vertex]);
          if (tin_[vertex] < tout_[adj_vertex.s_vertex]) {
            bridges_[adj_vertex.s_order] = 1;
            ++bridge_;
          }
        } else {
          tout_[vertex] = std::min(tout_[vertex], tin_[adj_vertex.s_vertex]);
        }
      }
    }
    colors_[vertex] = 2;
  }

  // Start of dfs from every s_vertex
  void DFS() {
    for (int i = 0; i < vertex_; ++i) {
      if (colors_[i + 1] == 0) {
        DfsProcess(0, i + 1);
      }
    }
  }

  // Delete all multi-edges
  void DeleteMultiEdge() {
    std::sort(bridge_edge_.begin(), bridge_edge_.end());
    for (int index = 0; index < static_cast<int>(bridge_edge_.size());) {
      int upd_index = index + 1;
      while (upd_index < static_cast<int>(bridge_edge_.size()) &&
             bridge_edge_[index].s_from == bridge_edge_[upd_index].s_from &&
             bridge_edge_[index].s_to == bridge_edge_[upd_index].s_to) {
        ++upd_index;
      }
      if (upd_index - index == 1) {
        AddTwoDirectEdge(bridge_edge_[index].s_from, bridge_edge_[index].s_to,
                         bridge_edge_[index].sb_order);
      }
      index = upd_index;
    }
  }

  // Add two direct edge
  void AddTwoDirectEdge(int from, int too, int order) {
    edges_[from].emplace_back(too, order);
    edges_[too].emplace_back(from, order);
  }
};

int main() {
  // input
  int vertex;
  int edge;
  std::cin >> vertex >> edge;
  Graph graph(vertex, edge);
  for (int i = 1; i <= edge; ++i) {
    int from;
    int too;
    std::cin >> from >> too;
    graph.AddOneDirectEdge(from, too, i);
  }

  // solve and output
  std::tuple<int, int, std::vector<int>> result = graph.Result();
  std::cout << std::get<0>(result) << '\n';
  for (int i = 0; i < std::get<1>(result); ++i) {
    if (std::get<2>(result)[i + 1] == 1) {
      std::cout << i + 1 << '\n';
    }
  }
}
