#include "isingmodel.h"
#include <array>
#include <cstdio>
#include <cstdlib>
#include <fstream>

constexpr size_t width = 100;
constexpr size_t height = 100;
constexpr size_t iterations = 1000;
constexpr std::array<int, 3> buckets = {100, 200, 250};

size_t get_random_index(size_t max) { return rand() % max; }

void bucketLoop(IsingModel &net, size_t iterations, int bucket,
                std::ofstream &file) {
  const int totalEnergy = bucket + net.calcTemp();
  file << 0 << '\t' << bucket << '\t' << net.calcMag() << '\n';
  for (int i = 0; i < iterations; i++) {
    size_t rand = get_random_index(net.size());
    int preChange = net.calcTemp();
    net.flip(rand);
    int postChange = net.calcTemp();
    int diff = postChange - preChange;
    if (diff < 0 && (bucket + diff < 0)) {
      net.flip(rand);
    } else {
      bucket += diff;
    }
    file << i + 1 << '\t' << bucket << '\t' << net.calcMag() << '\n';
  }
}

int main() {
  IsingModel net(width, height);
  char path[256];
  for (int i = 0; i < buckets.size(); i++) {
    net.set_all(1);
    sprintf(path, "./test_outputs/test%d.out", i + 1);
    std::ofstream file(path);
    bucketLoop(net, iterations, buckets[i], file);
  }
  return 0;
}