#include <iostream>
#include <vector>

#include <cstdint>

struct metal {
  metal(uint16_t price_in) : price(price_in) {}
  uint16_t price;
};

struct alchemist {
  alchemist(size_t from_t, size_t to_t, uint16_t price_in)
      : from(from_t), to(to_t), price(price_in) {}
  size_t from, to;
  uint16_t price;
};

std::vector<metal> create_metals(const size_t &metals_count) {
  std::vector<metal> new_vec(metals_count);
  for (size_t i = 0; i < new_vec.size(); i++) {
    uint16_t price{};
    std::cin >> price;
    metal temp(price);
    new_vec[i] = temp;
  }
  return new_vec;
}

std::vector<alchemist> create_alchemists(const size_t &alchemits_count) {
  std::vector<alchemist> new_vec(alchemits_count);
  for (auto &element : new_vec) {
    size_t from, to;
    uint16_t price;
    std::cin >> from >> to >> price;
    alchemist temp(from - 1, to - 1, price);
    element = temp;
  }
  return new_vec;
}

int **create_matrix(size_t size) {
  int **new_matrix = new int *[size];
  for (size_t i = 0; i < size; i++) {
    new_matrix[i] = new int[size];
  }

  for (size_t y = 0; y < size; y++) {
    for (size_t x = 0; x < size; x++) {
      new_matrix[y][x] = 0;
    }
  }
  return new_matrix;
}

void erase_graph(int **matrix, size_t size) {
  for (size_t i = 0; i < size; i++) {
    delete matrix[i];
  }
  delete matrix;
  return;
}

int solve_problem(const std::vector<metal> &metals,
                  const std::vector<alchemist> &alchemists) {
  int result = 0;
  int **matrix_graph = create_matrix(metals.size());

  erase_graph(matrix_graph, metals.size());
  return result;
}

int main() {
  size_t test_cases;
  std::cin >> test_cases;
  for (size_t i = 0; i < test_cases; ++i) {
    size_t metals_count;
    std::cin >> metals_count;
    std::vector<metal> metals = create_metals(metals_count);

    size_t alchemits_count;
    std::cin >> alchemits_count;
    std::vector<alchemist> alchemists = create_alchemists(alchemits_count);

    std::cout << solve_problem(metals, alchemists);
  }
  return 0;
}
