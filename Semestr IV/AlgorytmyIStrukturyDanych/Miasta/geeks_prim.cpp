#include <iostream>

size_t minKey(int key[], bool mstSet[], size_t matrix_size) {
  int min = INT_MAX, min_index;
  for (size_t v = 0; v < matrix_size; v++)
    if (mstSet[v] == false && key[v] < min) {
      min = key[v];
      min_index = v;
    }
  return min_index;
}

int **init_graph(size_t matrix_size) {
  int **new_graph = new int *[matrix_size];
  for (size_t i = 0; i < matrix_size; i++) {
    new_graph[i] = new int[matrix_size];
    for (size_t j = 0; j < matrix_size; j++) {
      new_graph[i][j] = 0;
    }
  }
  return new_graph;
}

int printMST(int parent[], int **graph, size_t matrix_size) {
  std::cout << "Edge \tWeight\n";
//   for (size_t i = 1; i < matrix_size; i++)
//     std::cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]]
//               << " \n";

  int answer = 0;
  for (size_t i = 1; i < matrix_size; i++) {
    answer = std::max(answer, graph[i][parent[1]]);
  }
  return answer;
}

void prim_MST(int **graph, size_t matrix_size) {
  int parent[matrix_size];
  int key[matrix_size];
  bool mstSet[matrix_size];
  for (size_t i = 0; i < matrix_size; i++) {
    key[i] = INT_MAX;
    mstSet[i] = false;
  }
  key[0] = 0;
  parent[0] = -1;
  for (size_t count = 0; count < matrix_size - 1; count++) {
    int u = minKey(key, mstSet, matrix_size);
    mstSet[u] = true;

    for (size_t v = 0; v < matrix_size; v++) {
      if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
        parent[v] = u;
        key[v] = graph[u][v];
      }
    }
  }
  std::cout << printMST(parent, graph, matrix_size) << '\n';
}

int main() {
  size_t test_cases;
  std::cin >> test_cases;
  for (size_t i = 0; i < test_cases; ++i) {
    size_t matrix_size, road_count;
    std::cin >> matrix_size >> road_count;
    int **graph = init_graph(matrix_size);
    for (size_t j = 0; j < road_count; j++) {
      size_t from, to;
      int weight;
      std::cin >> from >> to >> weight;
      graph[from][to] = weight;
      graph[to][from] = weight;
    }

    prim_MST(graph, matrix_size);

    for (size_t x = 0; x < matrix_size; x++) {
      delete graph[x];
    }
    delete graph;
  }
  return 0;
}