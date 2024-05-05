#include <algorithm>
#include <iostream>
#include <vector>

using map_edges = std::vector<std::vector<size_t>>;

struct mixture {
  mixture(size_t index_in, int value_in) : index(index_in), value(value_in) {}
  size_t index;
  int value;
};

struct {
  bool operator()(mixture first, mixture second) {
    return first.value < second.value;
  }
} mixture_compare;

// std::ostream &operator<<(std::ostream &output, std::vector<mixture> mix_in) {
//   output << "[ ";
//   for (auto mix : mix_in) {
//     output << " [ " << mix.index << " , " << mix.value << "], ";
//   }
//   output << "]";
//   return output;
// }

std::vector<mixture> input_value(size_t graph_size) {
  // std::cout << "Attempting to create input vector...\n";
  std::vector<mixture> new_values;
  for (size_t i = 0; i < graph_size; i++) {
    int temp_val;
    std::cin >> temp_val;
    mixture new_mix(i, temp_val);
    new_values.push_back(new_mix);
  }
  // std::cout << "Input values DONE!\n";
  return new_values;
}

map_edges input_transmition(size_t transmute_size) {
  map_edges new_transmition;
  // std::cout << "Attempting to create tranmistions vector...\n";
  for (size_t i = 0; i < transmute_size; i++) {
    size_t from, to;
    std::cin >> from >> to;
    std::vector<size_t> new_pair;
    new_pair.push_back(from - 1);
    new_pair.push_back(to - 1);
    new_transmition.push_back(new_pair);
  }
  // std::cout << "Tranmistions vector DONE!\n";
  return new_transmition;
}
const mixture *find_mixture(size_t id_node,
                            const std::vector<mixture> &mixtures) {
  for (auto &mix : mixtures) {
    if (mix.index == id_node)
      return &mix;
  }
  return nullptr;
}

int recur_search(size_t id_node, const std::vector<mixture> &mixtures,
                 const map_edges &edges, std::vector<bool> &visited) {
  const mixture *this_mixture = find_mixture(id_node, mixtures);
  int this_value = this_mixture->value;
  int potential = 0;
  visited[id_node] = true;
  for (auto &i : edges[id_node]) {
    if (!visited[i]) {
      int result = recur_search(i, mixtures, edges, visited);
      potential = std::max(result, potential);
    }
  }
  return std::max(potential, this_value);
}
int depth_search(size_t vec_iter, const std::vector<mixture> &mixtures,
                 const map_edges &edges, std::vector<bool> &visited) {
  const mixture *begin_mixture = &mixtures[vec_iter];
  int begin_value = begin_mixture->value;
  int end_value = begin_value;
  visited[begin_mixture->index] = true;
  for (auto &id_of_next : edges[begin_mixture->index]) {
    if (!visited[id_of_next]) {
      int potential = recur_search(id_of_next, mixtures, edges, visited);
      end_value = std::max(end_value, potential);
    }
  }
  return end_value - begin_value;
}

int find_max_profit(std::vector<mixture> &mixtures, const map_edges &edges) {
  int result = 0;
  std::sort(mixtures.begin(), mixtures.end(), mixture_compare);
  std::vector<bool> visited(mixtures.size(), false);
  for (size_t i = 0; i < mixtures.size(); i++) {
    result = std::max(result, depth_search(i, mixtures, edges, visited));
  }
  return result;
}

int main() {
  size_t test_cases;
  // std::cout << "Input amount of test cases: ";
  std::cin >> test_cases;
  for (size_t i = 0; i < test_cases; i++) {
    size_t mix_size, trans_size;
    std::cin >> mix_size >> trans_size;
    std::vector<mixture> mixtures = input_value(mix_size);
    map_edges edges = input_transmition(trans_size);
    map_edges adj_list(mix_size);
    for (auto i : edges) {
      adj_list[i[0]].push_back(i[1]);
    }
    std::cout << find_max_profit(mixtures, adj_list) << std::endl;
  }
  return 0;
}