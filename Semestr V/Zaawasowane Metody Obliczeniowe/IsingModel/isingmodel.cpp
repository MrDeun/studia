#include "isingmodel.h"
#include <algorithm>
#include <cstddef>
#include <numeric>

void IsingModel::set_all(int val) {
  if (val != 1 && val != -1) {
    fprintf(stderr,
            "ERROR: Incorrect val passed in: expected {-1,1}, received %d",
            val);
  }

  for (auto &element : model) {
    element = val;
  }
}
IsingModel::IsingModel(size_t width, size_t height)
    : width(width), height(height) {
  model.clear();
  model.reserve(width * height);
  std::fill(model.begin(), model.end(), 1);
  fprintf(stderr, "Model created %llux%llu", width, height);
}

void IsingModel::flip(size_t index) {
  if (index >= width * height) {
    fprintf(stderr, "ERROR: Tried to access value outside of the model\n");
    return;
  }
  model[index] *= -1;
}

double IsingModel::calcMag() {
  int sum = std::reduce(model.begin(), model.end(), 0, std::plus{});
  return double(sum) / double(width * height);
}

int IsingModel::calcTemp() {
  int res = 0;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      size_t next_x = (x + 1) % width;
      size_t next_y = (y + 1) % height;

      res += -(model[x + width * y] * model[next_x + width * y]);
      res += -(model[x + width * y] * model[x + width * next_y]);
    }
  }

  return res;
}