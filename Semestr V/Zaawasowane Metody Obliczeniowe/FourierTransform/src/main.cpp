#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>


constexpr double points1[16] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
constexpr size_t points1_size = sizeof(points1) / sizeof(double);

constexpr double points2[8] = {1.0, 0.707, 0, -0.707, -1.0, -0.707, 0.0, 0.707};
constexpr size_t points2_size = sizeof(points2) / sizeof(double);

void FourierTransform(const double *points, size_t points_size) {
  for (size_t n = 1; n < points_size; n++) {
    double a_n = 0.0;
    double b_n = 0.0;
    for (size_t i = 0; i < points_size; i++) {
      a_n += points[i] * std::sin(i * n * M_PI * 2 / points_size);
      b_n += points[i] * std::cos(i * n * M_PI * 2 / points_size);
    }
    if (fabs(a_n) < 0.001) {
      a_n = 0.0;
    }
    if (fabs(b_n) < 0.001) {
      b_n = 0.0;
    }
    std::cout << a_n / points_size << "\t" << b_n / points_size << "\n";
  }
  std::cout << "\n\n\n\n\n";
}

int main(int, char **) {
  std::cout << "Hello World\n";
  FourierTransform(points1,points1_size);
  FourierTransform(points2,points2_size);
}
