#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <map>

using trans_map = std::map<size_t,std::vector<size_t>>;

std::vector<int> create_mixtures(const size_t& mix_size){
  std::vector<int> new_mix = {};
  for (size_t i = 0; i < mix_size; i++) {
    int temp;
    std::cin >> temp;
    new_mix.push_back(temp);
  }
  std::cout << "Mixtures created\n";
  return new_mix;
}

trans_map init_map(const size_t& mix_size){
  trans_map new_map = {};
  for(size_t i=0; i<mix_size;i++){
    std::vector<size_t> new_list = {};
    new_map.insert(std::make_pair(i,new_list));
  }
  return new_map;
}

trans_map create_adjacent(const size_t& tran_size,const size_t& mix_size){
  std::map<size_t, std::vector<size_t>> fresh_map = init_map(mix_size);
  for (size_t i=0; i < tran_size; i++) {
    size_t from, to;
    std::cin >> from >> to;
    fresh_map.find(from)->second.push_back(to);
  }
  return fresh_map;
}

std::vector<bool> init_visited(size_t mix_size){
  std::vector<bool> new_vec = {};
  for (size_t i = 0; i < mix_size; i++) {
    new_vec.push_back(false);
  }
  return new_vec;
}

void recur_topologic(size_t index,const std::vector<int>& mixtures, const trans_map& adj_list, std::stack<size_t>& ans_stack, std::vector<bool>& visited){
  visited[index] = true;
  for (auto& element : adj_list.find(index)->second) {
    if(!visited[element])
      recur_topologic(element,mixtures, adj_list, ans_stack, visited);
  }
  ans_stack.push(index);
  return;
}

void topologic_sort(std::vector<int> mixtures, trans_map adj_list){
  std::stack<size_t> ans_stack{};
  std::vector<bool> visited = init_visited(mixtures.size());

  for (size_t i = 0;i<mixtures.size();i++) {
    if (!visited[i]) {
      recur_topologic(i,mixtures,adj_list,ans_stack,visited);
    }
  }

  while (!ans_stack.empty()) {
    std::cout << mixtures[ans_stack.top()] << " <- ";
    ans_stack.pop();
  }
}

int main(){
  size_t test_cases;
  std::cin >> test_cases;
  while (--test_cases) {
    std::cout << "CASE 0" << test_cases;
    size_t mix_size, tran_size;
    std::cin >> mix_size >> tran_size;
    std::vector<int> mixtures = create_mixtures(mix_size);
    trans_map adjacent_list = create_adjacent(tran_size,mix_size);
    topologic_sort(mixtures,adjacent_list);
  }
  return 0;
}