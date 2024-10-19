#include <cstddef>
#include <cstdio>
#include <vector>
class IsingModel {
private:
  size_t width;
  size_t height;
  std::vector<int> model;

public:
  IsingModel(size_t width, size_t height);
  ~IsingModel() {}
  void set_all(int value);
  size_t size() { return model.size(); }
  void flip(size_t index);
  int calcTemp();
  double calcMag();
};