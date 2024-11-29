#ifndef ISINGMODEL_H
#define ISINGMODEL_H

#include "IsingStats.h"
#include <cstdint>
#include <cstdlib>
#include <vector>
class SimulationModel {
private:
  std::vector<int8_t> Model;
  const size_t width;
  const size_t height;
  const size_t ModelSize;

  std::vector<int32_t> bucketValues;
  std::vector<double> magnetismValues;
  size_t randomIndex() {return rand()%ModelSize;}
  void flip(size_t idx);
  void flipAll();
  

public:
  SimulationModel(size_t width, size_t height);
  double CalculateMagnetism();
  int CalculateEnergy();
  void Simulate(size_t iterations, int bucket);
  SimulationResult results();
  void DEBUG_ShowModel();

};

#endif