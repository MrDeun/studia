#pragma once
#include <vector>

struct SimulationData{
  std::vector<int> bucket_stat;
  double averageMagnetism;
  SimulationData(std::vector<int> bs, double avgMag): bucket_stat(bs),averageMagnetism(avgMag){}
};