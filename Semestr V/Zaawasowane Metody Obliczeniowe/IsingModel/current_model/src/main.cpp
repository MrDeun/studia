#include "IsingModel.h"
#include "IsingStats.h"
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
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
    sprintf(filename, "results/bucket%2d.csv", i + 1);
    std::ofstream file(filename);
    file << "iteration" << ',' << "bucketValue" << ',' << "magnetism" << '\n';

    for (int j = 0; j < results[i].bucketResults.size(); j++) {
      file << j + 1 << ',' << results[i].bucketResults[j] << ','
           << results[i].magnetismResults[j] << '\n';
    }
  }
}

void save_count_to_files(const std::map<int32_t, uint32_t> &counts,
                         const char *filename) {
  std::ofstream filestream(filename);
  filestream << "value" << ',' << "count" << '\n';
  for (const auto &line : counts) {
    filestream << line.first << ',' << line.second << '\n';
  }
  filestream.close();
}

int main() {
  size_t width{}, height{}, iterations{};
  std::vector<int32_t> buckets = input(width, height, iterations);
  std::vector<SimulationResult> results;

  SimulationModel model(width, height);
  std::cerr << "Max energy: " << -2 * model.CalculateEnergy() << std::endl;
  for (auto bucket : buckets) {
    std::cerr << "Completion:  "
              << (double(bucket) / buckets[buckets.size() - 1]) * 100.0
              << std::flush << std::endl;
    model.Simulate(iterations, bucket);
    results.push_back(model.results());
  }
  std::cout << "iterations";
  std::string csv_entries = "";
  for(size_t i=0;i<results.size();i++){
    char buf[1024];
    sprintf(buf,",bucket%u,magnetism%u",i,i);
    std::cout << buf;
  }
  std::cout << '\n';
  for(size_t i=0;i<iterations;i++){
    std::cout << i+1 ;
    for (auto res : results) {
      std::cout <<','<< res.bucketResults[i] << ',' << res.magnetismResults[i];
    }
    std::cout << '\n';
  }
  return 0;
}