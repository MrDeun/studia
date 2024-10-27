#ifndef ISINGSTAT_H
#define ISINGSTAT_H

#include <cstdint>
#include <vector>
struct SimulationResult {
  std::vector<int32_t> bucketResults;
  std::vector<double> magnetismResults;

  double averageMagnetism;
  double averageTemp;

  SimulationResult(const std::vector<int32_t> &buckets,
                   const std::vector<double> magnetism)
      : bucketResults(buckets), magnetismResults(magnetism),
        averageMagnetism(0.0), averageTemp(0.0) {}
};

#endif