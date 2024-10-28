#include "Statistics.h"
#include <cstdint>
#include <map>

StatisticalModel::StatisticalModel() : avgEnergy(0.0), avgMagnetism(0.0) {}
std::map<int32_t, uint32_t> StatisticalModel::countBuckets() {
  std::map<int32_t, uint32_t> res{};
  for (const int32_t &val : buckets) {
    res[val]++;
  }
  return res;
}