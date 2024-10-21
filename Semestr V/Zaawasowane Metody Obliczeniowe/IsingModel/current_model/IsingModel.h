#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <ctime>

#include "IsingStats.h"

template <size_t width, size_t height> class SimulationModel {
private:
  bool defaultState;
  std::array<int, width * height> Model;
  std::vector<int> bucketEnergies;
  double averageMagnetism;
  const size_t ModelSize;
  size_t randomIndex() { return rand() % ModelSize; }
  void flip(size_t index) { Model[index] *= -1; }

  int calculateEnergy();
  double calculateMagnet();
  void reset() {
    bucketEnergies.clear();
    std::fill(Model.begin(), Model.end(), 1);
  }

public:
  SimulationModel()
      : averageMagnetism(0.0), ModelSize(width * height), defaultState(true) {
    srand(time(nullptr));
    std::fill(Model.begin(), Model.end(), 1);
  }

  SimulationData results(){
    return SimulationData(bucketEnergies,averageMagnetism);
  }

  void Simulate(size_t iterations, int bucket) ;
};