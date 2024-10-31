#include "IsingModel.h"
#include "IsingStats.h"
#include "Statistics.h"
#include <cstdint>
#include <cstdio>
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
    sprintf(filename, "results/bucket%2d.csv", i + 1);
    std::ofstream file(filename);
    for (int j = 0; j < results[i].bucketResults.size(); j++) {
      file << j + 1 << ',' << results[i].bucketResults[j] << ','
           << results[i].magnetismResults[j] << '\n';
    }
  }
}

void save_count_to_files(const std::map<int32_t, uint32_t>& counts,const char* filename){
  std::ofstream filestream(filename);
  for(const auto& line : counts){
    filestream << line.first << ','<<line.second<<'\n';
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
    model.Simulate(iterations, bucket);
    results.push_back(model.results());
  }
  save_to_files(results);
  StatisticalModel stats;
  for (size_t i=0;i<results.size();i++) {
    char buf[256];
    stats.loadData(results[i]);
    std::map<int32_t, uint32_t> counts = stats.countBuckets();
    sprintf(buf,"results/bucketcount%d.csv",i+1);
    save_count_to_files(counts,buf);
    
  }

  return 0;
}