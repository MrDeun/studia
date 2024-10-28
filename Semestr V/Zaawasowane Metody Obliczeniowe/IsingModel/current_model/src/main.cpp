#include "IsingModel.h"
#include "IsingStats.h"
#include "Statistics.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

std::vector<int32_t> input(size_t &width, size_t &height, size_t &iterations) {
  std::cin >> width >> height >> iterations;
  size_t bucketSize;
  std::cin >> bucketSize;
  std::vector<int32_t> buckets;
  for (int i = 0; i < bucketSize; i++) {
    int32_t temp;
    std::cin >> temp;
    buckets.push_back(temp);
  }
  return buckets;
}

void save_to_files(const std::vector<SimulationResult> &results) {
  for (int i = 0; i < results.size(); i++) {
    char filename[256];
    sprintf(filename, "results/bucket%d.out", i + 1);
    std::ofstream file(filename);
    for (int j = 0; j < results[i].bucketResults.size(); j++) {
      file << results[i].bucketResults[j] << ','
           << results[i].magnetismResults[j] << '\n';
    }
  }
}

int main() {
  size_t width{}, height{}, iterations{};
  std::vector<int32_t> buckets = input(width, height, iterations);
  std::vector<SimulationResult> results;

  SimulationModel model(width, height);
  std::cerr << "Max energy: " << -2 * model.CalculateEnergy() << std::endl;
  for (auto bucket : buckets) {
    model.Simulate(iterations, bucket);
    results.push_back(model.results());
  }
  // save_to_files(results);
  StatisticalModel stats;
  for (auto res : results) {
    stats.loadData(res);
    std::map<int32_t, uint32_t> counts = stats.countBuckets();
    for (auto element : counts) {
      std::cout << element.first << ": " << element.second << std::endl;
    }
  }

  return 0;
}