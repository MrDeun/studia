#pragma once
#include "isingmodel.hpp"
#include <cstddef>
#include <cstdio>
#include <numeric>

double IsingModel::calculateMag() {
  int sum = std::reduce(vec.begin(), vec.end(), 0, std::plus{});
  return double(sum) / vec.size();
}

int IsingModel::calculateTemp() {}

void IsingModel::set_all(IsingValue val) {
  for (auto &in : vec) {
    in = val;
  }
  return;
}

void IsingModel::set_at(size_t x, size_t y, IsingValue val) {
  if (x > width || y > height) {
    fprintf(stderr, "WARNING: Tried to write outside of Model's range!\n");
    return;
  }
  vec[x + width * y] = val;
}