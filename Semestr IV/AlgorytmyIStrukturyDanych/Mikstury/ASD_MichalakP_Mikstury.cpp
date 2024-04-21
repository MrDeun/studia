#include <vector>
#include <stack>
#include <iostream>

using map_edges = std::vector<std::vector<size_t>>;

std::vector<int> input_value(size_t graph_size){
  std::vector<int> new_values;
  for (size_t i  = 0;i<graph_size;i++) {
    int temp_val;
    std::cin >> temp_val;
    new_values.push_back(temp_val);
  }
  return new_values;
}

std::vector<std::vector<size_t>> input_transmition(size_t transmute_size) {
  std::vector<std::vector<size_t>> new_transmition;
  for (size_t i=0; i < transmute_size; transmute_size++) {
    size_t from,to;
    std::cin >>from>>to;
    std::vector<size_t> new_pair;
    new_pair.push_back(from-1);
    new_pair.push_back(to-1);
    new_transmition.push_back(new_pair);
  }
  return new_transmition;
}

void topologicalSort_recur(size_t current_index,
                          map_edges& adj_list,
                          std::vector<bool> visited,
                          std::stack<size_t> stack_index){
  visited[current_index] = true;
  for (auto i : adj_list[current_index]) {
    if (!visited[i]) {
      topologicalSort_recur(i, adj_list, visited,stack_index);
    }
  }
  stack_index.push(current_index);
}

std::stack<size_t> topologicalSort(map_edges& adj_list,size_t graph_size){
  std::stack<size_t> stack_index;
  std::vector<bool> visited(graph_size,false);

  for (size_t i = 0;i<graph_size;i++) {
    if(!visited[i]){
      topologicalSort_recur(i,adj_list,visited,stack_index);
    }
  }
  return stack_index;
}

int main(){
  size_t test_cases;
  std::cin >> test_cases;
  for (size_t i = 0;i<test_cases;i++) {
    size_t graph_size,transmute_size;
    std::cin >> graph_size >> transmute_size;

    std::vector<int> values = input_value(graph_size);
    std::vector<std::vector<size_t>> edges = input_transmition(transmute_size);
    std::vector<std::vector<size_t>> adj_list(graph_size);

    for (auto j : edges) {
      adj_list[j[0]].push_back(j[1]);
    }
    std::stack<size_t> result = topologicalSort(adj_list,graph_size);
    while (!result.empty()) {
      std::cout << values[result.top()];
      result.pop();
    }
  }
  return 0;
}