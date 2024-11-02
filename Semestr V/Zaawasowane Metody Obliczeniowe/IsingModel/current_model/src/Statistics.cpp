#include "Statistics.h"
#include <cstdint>
#include <map>
#include <numeric>

StatisticalModel::StatisticalModel() : avgEnergy(0.0), avgMagnetism(0.0) {}
std::map<int32_t, uint32_t> StatisticalModel::countBuckets() {
  std::map<int32_t, uint32_t> temp{}, res{};
  for (const int32_t &val : buckets) {
    temp[val]++;
  }
  for (int i = 0; i < 16 * 4; i += 4) {
    res[i] = temp[i];
  }
  return res;
}

std::pair<double, double> StatisticalModel::linearRegression(
    const std::map<int32_t, uint32_t> &bucketCounts) {
  const int64_t Sx = std::reduce(bucketCounts.begin(),bucketCounts.end(),0,getFirst);
  const int64_t Sy = std::reduce(bucketCounts.begin(),bucketCounts.end(),0,getSecond);
  const int64_t Sxy = std::reduce(bucketCounts.begin(),bucketCounts.end(),0,getCombination);
  const int64_t Sxx = std::reduce(bucketCounts.begin(),bucketCounts.end(),0,getSquaredFirst);
  const size_t count = bucketCounts.size();

  const int64_t Sx2 = Sx * Sx;
  const double a = double(count * Sxy - Sx * Sy)/double(count * Sxx - Sx2);
  
}
