#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using transmutate = std::pair<size_t,size_t>;

std::vector<transmutate> fill_transmutes(size_t trans_size){
  std::vector<transmutate> transmutes = {};
  while(trans_size--){
    size_t from, to;
    std::cin >> from >> to;
    transmutes.push_back(std::make_pair(from-1, to-1));
  }
  return transmutes;
}

std::vector<int> fill_mixtures(size_t mix_size){
  std::vector<int> mixtures = {};
  while(mix_size--){
    int temp_value;
    std::cin >> temp_value;
    mixtures.push_back(temp_value);
  }
  return mixtures;
}

void view_stack(std::stack<int> result);

std::vector<bool> init_visits(size_t mix_size){
  std::vector<bool> new_visits;
  while (mix_size--) {
    new_visits.push_back(false);
  }
}

void toposort(std::vector<int> mixtures, std::vector<transmutate> transmutes){
  std::stack<int> result;
  std::vector<bool> visited = init_visits(mixtures.size());
  view_stack(result);
}

int main() {
  size_t test_cases;
  std::cin >> test_cases;
  while (test_cases--) {
    size_t mix_size{}, trans_size{};
    std::cin >> mix_size >> trans_size;
    std::vector<int> mixtures = fill_mixtures(mix_size);
    std::vector<transmutate> transmutes = fill_transmutes(trans_size);
    toposort(mixtures,transmutes);
  }
}