#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "IsingStats.h"

class SimulationModel {
private:
  bool defaultState;
  size_t width, height;
  std::vector<int8_t> Model;
  std::vector<int> bucketEnergies;
  double averageMagnetism;
  
  
  size_t randomIndex() { return rand() % (width*height); }
  void flip(size_t index) { Model[index] *= -1; }
  void reset(); 

public:
  int calculateEnergy();
  double calculateMagnet();
  void flipAll(){
    for (auto& arrow : Model) {
      arrow *= -1;
    }
  }
  SimulationModel(size_t width, size_t height)
      : averageMagnetism(0.0), width(width), height(height), defaultState(true) {
    srand(time(nullptr));
    Model.reserve(width*height);
    std::fill(Model.begin(), Model.end(), 1);
  }

  SimulationData results(){
    return SimulationData(bucketEnergies,averageMagnetism);
  }

  void Simulate(size_t iterations, int bucket) ;
};