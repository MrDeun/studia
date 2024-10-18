#pragma once

#include <cstddef>
#include <vector>
enum IsingValue {
  POSITIVE = 1,
  NEGATIVE = -1,
};

class IsingModel {
  private:
    size_t width;
    size_t height;
    std::vector<IsingValue> vec;
  public:
    IsingModel(size_t width, size_t height): width(width), height(height){
      if (!vec.empty()) {
        vec.clear();
      }
      vec.reserve(width*height);
    }
    void set_all(IsingValue val);
    void set_at(size_t x, size_t y, IsingValue val);
    int calculateTemp();
    double calculateMag();
};