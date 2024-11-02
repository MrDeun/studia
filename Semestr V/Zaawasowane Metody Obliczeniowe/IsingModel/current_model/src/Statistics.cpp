#include "Statistics.h"
#include <cmath>
#include <cstdint>
#include <map>
#include <numeric>
#include <utility>

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

double StatisticalModel::averageMagnetism() {
  return double(std::reduce(magnets.begin() + 4000, magnets.end(), 0,
                            std::plus{})) /
         double(magnets.size() - 4000);
}

std::pair<double, double> StatisticalModel::linearRegression(
    const std::map<int32_t, uint32_t> &bucketCounts) {
  int64_t count = bucketCounts.size();
  int64_t Sxx = 0, Sy = 0, Sx = 0, Sxy = 0;
  for (auto pair : bucketCounts) {
    Sx += pair.first;
    Sy += pair.second;
    Sxy += pair.first * pair.second;
    Sxx += pair.first * pair.first;
  }
  const double avgX = double(Sx) / count;
  const double avgY = double(Sy) / count;
  const double avgXY = double(Sxy) / count;
  const double avgXX = double(Sxx) / count;
  const double avgX2 = double(Sx * Sx) / count;
  const int64_t Sx2 = Sx * Sx;

  const double a = (avgXY - avgX * avgY) / (avgXX - avgX2);
  const double b = avgY - a * avgX;

  return std::pair<double, double>(a, b);
}

std::pair<double, double> StatisticalModel::linearRegression(
    const std::map<double,double> &bucketCounts) {
  int64_t count = bucketCounts.size();
  double Sxx = 0, Sy = 0, Sx = 0, Sxy = 0;
  for (auto pair : bucketCounts) {
    Sx += pair.first;
    Sy += pair.second;
    Sxy += pair.first * pair.second;
    Sxx += pair.first * pair.first;
  }
  const double avgX = double(Sx) / count;
  const double avgY = double(Sy) / count;
  const double avgXY = double(Sxy) / count;
  const double avgXX = double(Sxx) / count;
  const double avgX2 = double(Sx * Sx) / count;
  const double Sx2 = Sx * Sx;

  const double a = (avgXY - avgX * avgY) / (avgXX - avgX2);
  const double b = avgY - a * avgX;

  return std::pair<double, double>(a, b);
}

std::map<double,double> StatisticalModel::powerScaling(const std::map<int32_t,uint32_t>& counts){
  std::map<double,double> new_counts = {};
  for (auto pair : counts) {
    new_counts[std::log(pair.first)] = std::log(pair.second);
  }
  return new_counts;
}
