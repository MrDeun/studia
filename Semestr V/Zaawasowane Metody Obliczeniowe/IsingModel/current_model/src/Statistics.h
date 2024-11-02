#ifndef STATISTICS_H
#define STATISTICS_H

#include "IsingStats.h"
#include <cassert>
#include <cstdint>
#include <map>
#include <vector>

class StatisticalModel {
private:
  std::vector<double> magnets;
  std::vector<int32_t> buckets;

  double avgMagnetism;
  double avgEnergy;

  inline static auto getFirst = [](std::pair<int32_t,uint32_t> pair){return pair.first;};
  inline static auto getSecond = [](std::pair<int32_t,uint32_t> pair){return pair.second;};
  inline static auto getSquaredFirst = [](std::pair<int32_t,uint32_t> pair){return pair.first*pair.first;};
  inline static auto getSquaredSecond = [](std::pair<int32_t,uint32_t> pair){return pair.second*pair.second;};
  inline static auto getCombination = [](std::pair<int32_t,uint32_t> pair) {return pair.first*pair.second;};

public:
  StatisticalModel();
  void loadData(const SimulationResult &res) {
    this->magnets = res.magnetismResults;
    this->buckets = res.bucketResults;
    avgMagnetism = 0.0;
    avgEnergy = 0.0;
  }

  size_t size() {
    assert(magnets.size() == buckets.size());
    return magnets.size();
  }

  std::map<int32_t, uint32_t> countBuckets();

  std::pair<double, double>
  linearRegression(const std::map<int32_t, uint32_t> &countBucket);
};

#endif