#include <algorithm>
#include <vector>
#include <iostream>
using map_edges = std::vector<std::vector<size_t>>;

struct mixture{
  mixture(size_t index_in, int value_in): 
    index(index_in), 
    value(value_in){}
  size_t index;
  int value;
};

std::vector<mixture> input_value(size_t graph_size){
  std::cout << "Attempting to create input vector...\n";
  std::vector<mixture> new_values;
  for (size_t i  = 0;i<graph_size;i++) {
    int temp_val;
    std::cin >> temp_val;
    mixture new_mix(i,temp_val);
    new_values.push_back(new_mix);
  }
  std::cout << "Input values DONE!\n";
  return new_values;
}

map_edges input_transmition(size_t transmute_size) {
  map_edges new_transmition;
  std::cout << "Attempting to create tranmistions vector...\n";
  for (size_t i=0; i < transmute_size; i++) {
    size_t from,to;
    std::cin>>from>>to;
    std::vector<size_t> new_pair;
    new_pair.push_back(from-1);
    new_pair.push_back(to-1);
    new_transmition.push_back(new_pair);
  }
  std::cout << "Tranmistions vector DONE!\n";
  return new_transmition;
}

void sort_by_value(std::vector<mixture>& mixtures){
  std::cout << "Sorting mixtures by values...\n";
  bool swapped;
  for (size_t i = 0 ; i < mixtures.size()-1; i++) {
    swapped = false;
    for (size_t j = 0;j < mixtures.size()-i-1;j++) {
      if (mixtures[j].value > mixtures[j+1].value) {
        std::swap(mixtures[j],mixtures[j+1]);
        swapped = true;
      }
    }
    if (swapped) {
      break;}}
  std::cout << "Finished sorting!\n";
  return;
}

int recur_search(size_t this_index, const std::vector<mixture>& mixtures, const map_edges& edges,std::vector<bool>& visited){
  std::cout << "Recursive search started\n";
  visited[this_index] = true;
  int this_value = mixtures[this_index].value;
  int next_value = 0;
  if (!edges[this_index].empty()) {
    for (auto index:edges[this_index]) {
      if (!visited[index]) {
        next_value = std::max(next_value,recur_search(index, mixtures, edges, visited));
      }}}
  std::cout << "Recursive search finished\n";
  return std::max(this_value,next_value);
}

int depth_search(size_t id_begin,const std::vector<mixture>& mixtures,const map_edges& edges){
  std::cout << "Started new depth search\n";
  int begin_value = mixtures[id_begin].value;
  int end_value = begin_value;
  std::vector<bool> visited(mixtures.size(),false);
  visited[id_begin] = true;
  if (!edges[id_begin].empty()) {
    for (size_t index : edges[id_begin]) {
    if (!visited[index]) {
      int recur_end = recur_search(index,mixtures,edges,visited);
      end_value = std::max(end_value,recur_end);
    }}}
  std::cout << "Finished depth search!\n";
  return end_value - begin_value;
}
int find_max_profit(std::vector<mixture>& mixtures,const map_edges& edges){
  int result = 0;
  sort_by_value(mixtures);
  for (size_t i=0; i<mixtures.size(); i++) {
    result = std::max(result,depth_search(i,mixtures, edges));
  }
  return result;
}


int main(){
  size_t test_cases;
  std::cout << "Input amount of test cases: ";
  std::cin >> test_cases;
  for (size_t i = 0;i<test_cases;i++) {
    size_t mix_size, trans_size;
    std::cin >> mix_size >> trans_size;
    std::vector<mixture> mixtures = input_value(mix_size);
    map_edges edges = input_transmition(trans_size);
    map_edges adj_list(mix_size);
    for (auto i  : edges) {
      adj_list[i[0]].push_back(i[1]);
    }
    std::cout << find_max_profit(mixtures,adj_list) << std::endl;
  }
  return 0;
}