#include "isingmodel.hpp"
#include <cstddef>
#include <cstdio>
#include <numeric>

#define POSITIVE 1
#define NEGATIVE -1

double IsingModel::calculateMag() {
  int sum = std::reduce(vec.begin(), vec.end(), 0, std::plus{});
  return double(sum) / vec.size();
}

int IsingModel::calculateTemp() {
  int sum = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int next_x = (x + 1) % width;
      int next_y = (y + 1) % height;

      sum += -(vec[x + width * y] * vec[next_x + width * y]);
      sum += -(vec[x + width * y] * vec[x + width * next_y]);
    }
  }
  return sum;
}

void IsingModel::set_all(int val) {
  for(int i=0;i<vec.size();i++){
    vec[i] = val;
  }
  return;
}

void IsingModel::flip(size_t x, size_t y) {
  if (x > width || y > height) {
    fprintf(stderr, "WARNING: Tried to write outside of Model's range!\n");
    return;
  }
  int& val =vec[x + width * y]; 
  switch (val) {
  case POSITIVE:
    val = NEGATIVE; 
    break;
  case NEGATIVE:
    val = POSITIVE;
    break;
  default:
    fprintf(stderr, "Model has incorrect value of %d\n", vec[x + width * y]);
    break;
  }
  
}

void IsingModel::flip(size_t index) {
  if (index > width*height) {
    fprintf(stderr, "WARNING: Tried to write outside of Model's range!\n");
    return;
  }
  int& val =vec[index]; 
  switch (val) {
  case POSITIVE:
    val = NEGATIVE; 
    break;
  case NEGATIVE:
    val = POSITIVE;
    break;
  default:
    fprintf(stderr, "Model has incorrect value of %d\n", vec[index]);
    break;
  }
}