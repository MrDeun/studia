#include <cstdint>
#include <iostream>

int main() {
  const uint16_t resolution = 16;
  for (uint16_t height = 0; height < resolution; height++) {
    for (uint16_t width = 0; width < resolution; width++) {
      if (width < height) {
        std::cout << "X";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  for (uint16_t height = 0; height < resolution; height++) {
    for (uint16_t width = 0; width < resolution; width++) {
      if (width > height) {
        std::cout << "X";
      } else {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  return 0;
}
