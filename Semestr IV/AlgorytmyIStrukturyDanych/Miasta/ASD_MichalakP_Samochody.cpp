#include <algorithm>
#include <iostream>
#include <vector>


struct road {
  road(size_t i_from, size_t i_to, int i_distance)
      : from(i_from), to(i_to), distance(i_distance) {}
  size_t from;
  size_t to;
  int distance;
};

bool by_distance(road &first, road &second) {
  return first.distance < second.distance;
}

std::vector<size_t> create_towns(size_t towns_count) {
  std::vector<size_t> new_towns(towns_count);
  for (int i = 0; i < new_towns.size(); i++) {
    new_towns[i] = i;
  }
  return new_towns;
}

std::vector<road> create_roads(size_t road_count) {
  std::vector<road> new_roads(road_count);
  for (auto it : new_roads) {
    size_t begin, end;
    int distance;
    std::cin >> begin >> end >> distance;
    road temp_road(begin, end, distance);
    it = temp_road;
  }
  return new_roads;
}

int find_longest_road(const std::vector<size_t> &towns,
                      std::vector<road> &roads) {
  std::sort(roads.begin(), roads.end(), by_distance);
  int result;
  
  return result;
}

int main() {
  size_t test_cases;
  std::cin >> test_cases;
  for (int i = 0; i < test_cases; i++) {
    size_t towns_count, road_count;
    std::cin >> towns_count >> road_count;
    std::vector<size_t> towns = create_towns(towns_count);
    std::vector<road> roads = create_roads(road_count);
    std::cout << find_longest_road(towns, roads);
  }
}
