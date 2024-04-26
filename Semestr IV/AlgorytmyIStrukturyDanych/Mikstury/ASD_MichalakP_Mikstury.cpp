#include <vector>
#include <iostream>

using map_edges = std::vector<std::vector<size_t>>;

std::vector<int> input_value(size_t graph_size){
  std::cout << "Attempting to create input vector...\n";
  std::vector<int> new_values;
  for (size_t i  = 0;i<graph_size;i++) {
    int temp_val;
    std::cin >> temp_val;
    new_values.push_back(temp_val);
  }
  std::cout << "Input values DONE!\n";
  return new_values;
}

map_edges input_transmition(size_t transmute_size, const std::vector<int>& values) {
  map_edges new_transmition;
  std::cout << "Attempting to create tranmistions vector...\n";
  for (size_t i=0; i < transmute_size; i++) {
    size_t from,to;
    std::cin>>to;
    std::cin>>from;
    if (values[from-1] < values[to-1]) {
      std::vector<size_t> new_pair;
      new_pair.push_back(from-1);
      new_pair.push_back(to-1);
      new_transmition.push_back(new_pair);
    } else continue;
  }
  std::cout << "Tranmistions vector DONE!\n";
  return new_transmition;
}
void topologicalSort_recur(size_t current_index,const map_edges& adj_list,std::vector<size_t>& result,std::vector<bool>& visited){
  visited[current_index] = true;
  for (size_t i:adj_list[current_index]) {
    if (!visited[i]) {
      topologicalSort_recur(i,adj_list,result,visited);
    }
  }
  result.push_back(current_index);
}

std::vector<size_t> topologicalSort(const map_edges& adj_list,const size_t& graph_size){
  std::vector<size_t> result;
  std::vector<bool> visited(graph_size,false);
  for (size_t i = 0;i<graph_size;i++) {
    if(!visited[i])
      topologicalSort_recur(i,adj_list,result,visited);
  }
  return result;
}

int main(){
  size_t test_cases;
  std::cout << "Input amount of test cases: ";
  std::cin >> test_cases;
  for (size_t i = 0;i<test_cases;i++) {
    size_t graph_size,transmute_size;
    std::cin >> graph_size >> transmute_size;
    std::vector<int> values = input_value(graph_size);
    map_edges edges = input_transmition(transmute_size,values);
    map_edges adj_list(graph_size);
    std::cout << "Attempting to create adjacenty list\n";
    for (auto j : edges) {
      adj_list[j[0]].push_back(j[1]);
    }
    std::cout << "Created adjacnety list no. \n";
    std::vector<size_t> result = topologicalSort(adj_list, graph_size);
    int max_profit = 0;
    for (size_t i = 0; i < result.size()-1; i++) {
      if (values[result[i]] < values[result[i+1]]) {
        max_profit += values[result[i+1]] - values[result[i]];
      }
    }
    
    std::cout<< max_profit << std::endl;
  }
  return 0;
}