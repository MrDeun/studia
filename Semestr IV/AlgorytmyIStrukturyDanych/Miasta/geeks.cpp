#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

class DSU {
  int *parent;
  int *rank;

public:
  DSU(size_t size) {
    parent = new int[size];
    rank = new int[size];
    for (size_t i = 0; i < size; i++) {
      parent[i] = -1;
      rank[i] = 1;
    }
  }

  int find(int i) {
    if (parent[i] == -1) {
      return 1;
    }
    return parent[i] = find(parent[i]);
  }

  void unite(int x, int y) {
    int s1 = find(x);
    int s2 = find(y);

    if (s1 != s2) {
      if (rank[s1] < rank[s2]) {
        parent[s1] = s2;
      } else if (rank[s1] > rank[s2]) {
        parent[s2] = s1;
      } else {
        parent[s2] = s1;
        rank[s1]++;
      }
    }
  }
};

class Graph {
  std::vector<std::vector<int>> edgeList;
  size_t size;

public:
  Graph(size_t size_i) : size(size_i) {}
  void addEdge(int from, int to, int price) {
    edgeList.push_back({price, from, to});
  }
  void kruskal_mst() {
    std::sort(edgeList.begin(), edgeList.end());
    DSU tree(size);
    int answer = 0;
    for (auto edge : edgeList) {
      int price = edge[0];
      int from = edge[1];
      int to = edge[2];
      if (tree.find(from) != tree.find(to)) {
        tree.unite(from, to);
        answer = std::max(answer, price);
      }
    }
    std::cout << answer;
  }
};

std::vector<size_t> create_town(size_t towns_n) {
  std::vector<size_t> new_vec(towns_n);
  for (size_t i = 0; i < new_vec.size(); ++i) {
    new_vec[i] = i;
  }
  return new_vec;
}

int main() {
  size_t test_cases{};
  std::cin >> test_cases;
  for (size_t i = 0; i < test_cases; i++) {
    size_t towns_n, roads_n;
    std::cin >> towns_n >> roads_n;
    std::vector<size_t> town_vec = create_town(towns_n);
    Graph this_case(roads_n);
    for (size_t j = 0; j < roads_n; ++j) {
      int from, to, price;
      std::cin >> from >> to >> price;
      this_case.addEdge(from, to, price);
    }
    this_case.kruskal_mst();
  }
  return 0;
}