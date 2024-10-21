#pragma once
#include "IsingStats.h"
#include <cstddef>
#include <vector>
class IsingStatistics {
private:
  std::vector<int> bucketStats;
  bool ready;
  double avgMagnetism;
  double (*CalculateTemp)();
  double calculateFromLog();
  double calculateFromPow();

public:
  IsingStatistics() : avgMagnetism(0.0), ready(false) {
    CalculateTemp = nullptr;
  }
  ~IsingStatistics() {}
  void LoadStatisticks(SimulationData data) {
    avgMagnetism = data.averageMagnetism;
    bucketStats = data.bucket_stat;
  };
};