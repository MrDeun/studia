#ifndef ISINGSTAT_H
#define ISINGSTAT_H

#include <cassert>
#include <cstdint>
#include <vector>
struct SimulationResult {
  std::vector<int32_t> bucketResults;
  std::vector<double> magnetismResults;
  SimulationResult(const std::vector<int32_t> &buckets,
                   const std::vector<double> &magnetism)
      : bucketResults(buckets), magnetismResults(magnetism) {
    assert(bucketResults.size() == magnetism.size());
  }
};

#endif