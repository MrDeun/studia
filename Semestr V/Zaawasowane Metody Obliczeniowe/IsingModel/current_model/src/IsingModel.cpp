#include "IsingModel.h"
#include "IsingStats.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>

SimulationModel::SimulationModel(size_t _width, size_t _height)
    : width(_width), height(_height), ModelSize(_width * _height) {
  srand(time(nullptr));
  Model.resize(ModelSize);
  std::fill(Model.begin(), Model.end(), 1);
  assert(Model.size() == ModelSize);
  assert(_width * _height == ModelSize);
}

void SimulationModel::flip(size_t idx) { Model[idx] *= -1; }

double SimulationModel::CalculateMagnetism() {
  const int total = std::reduce(Model.begin(), Model.end(), 0, std::plus{});
  return double(total) / double(Model.size());
}

int SimulationModel::CalculateEnergy() {
  int res = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      size_t next_x = (x + 1) % width;
      size_t next_y = (y + 1) % height;

      res += -(Model[x + width * y] * Model[next_x + width * y]);
      res += -(Model[x + width * y] * Model[x + width * next_y]);
    }
  }
  return res;
}

SimulationResult SimulationModel::results() {
  SimulationResult result(bucketValues, magnetismValues);

  bucketValues.clear();
  magnetismValues.clear();

  return result;
}

void SimulationModel::Simulate(size_t iterations, int bucket) {
  int preChange = CalculateEnergy();
  const int totalEnergy =
      bucket + preChange; // for W,H = 36, should be -2592 + bucket
  for (int i = 0; i < iterations; i++) {
    const size_t idx = randomIndex();
    flip(idx);
    int postChange = CalculateEnergy();
    if (bucket + (preChange - postChange) < 0) {
      flip(idx);
      postChange = preChange;
    } else {
      bucket += (preChange - postChange);
      preChange = postChange;
    }

    assert(bucket + postChange == totalEnergy);
    bucketValues.push_back(bucket);
    magnetismValues.push_back(CalculateMagnetism());
  }
  std::fill(Model.begin(), Model.end(), 1);
}

void SimulationModel::DEBUG_ShowModel() {
  for (int i = 0; i < ModelSize; i++) {
    std::cout << Model[i];
  }
}
