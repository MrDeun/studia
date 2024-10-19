#pragma once

#include <cstddef>
#include <vector>
class IsingModel {
  private:
    size_t width;
    size_t height;
    std::vector<int> vec;
  public:
    IsingModel(size_t width, size_t height): width(width), height(height){
      if (!vec.empty()) {
        vec.clear();
      }
      vec.reserve(width*height);
    }
    void set_all(int val);
    void flip(size_t x, size_t y);
    void flip(size_t index);
    int calculateTemp();
    size_t size() {return width*height;}
    double calculateMag();
};