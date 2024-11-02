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

public:
  double averageMagnetism();
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
  std::pair<double, double>
  linearRegression(const std::map<double,double> &countBucket);

  std::map<double, double>
  powerScaling(const std::map<int32_t, uint32_t> &countBucket);
};

#endif