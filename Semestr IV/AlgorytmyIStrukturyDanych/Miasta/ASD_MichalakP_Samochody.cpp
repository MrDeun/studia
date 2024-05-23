#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>
struct road {
  road(size_t i_from, size_t i_to, int i_distance)
      : from(i_from), to(i_to), distance(i_distance) {}
  size_t from;
  size_t to;
  int distance;
};

std::ostream &operator<<(std::ostream &output, road road_in) {
  output << '{' << road_in.from << ", " << road_in.to << ", "
         << road_in.distance << " }";
  return output;
}

template <class Type>
std::ostream &operator<<(std::ostream &output, std::vector<Type> vec_in) {
  output << "[";
  for (auto i : vec_in) {
    output << i << ", ";
  }
  output << "]";
  return output;
}

bool by_distance(road &first, road &second) {
  return first.distance < second.distance;
}

std::vector<size_t> create_towns(size_t towns_count) {
  std::vector<size_t> new_towns(towns_count);
  for (size_t i = 0; i < new_towns.size(); i++) {
    new_towns[i] = i;
  }
  return new_towns;
}

std::vector<road> create_roads(size_t road_count) {
  std::vector<road> new_roads;
  for (size_t i = 0; i < road_count; i++) {
    size_t new_from, new_to;
    int new_distance;

    std::cin >> new_from >> new_to >> new_distance;
    road new_road(new_from, new_to, new_distance);
    new_roads.push_back(new_road);
  }
  return new_roads;
}

int find_longest_road(const std::vector<size_t> &towns,
                      std::vector<road> &roads) {
  std::sort(roads.begin(), roads.end(), by_distance);
  int result = 0;
  std::cout << roads << '\n';
  return result;
}

int main() {
  size_t test_cases;
  std::cin >> test_cases;
  for (size_t i = 0; i < test_cases; i++) {
    size_t towns_count, road_count;
    std::cin >> towns_count >> road_count;
    std::vector<size_t> towns = create_towns(towns_count);
    std::vector<road> roads = create_roads(road_count);
    std::cout << find_longest_road(towns, roads) << " \n";
  }
}
