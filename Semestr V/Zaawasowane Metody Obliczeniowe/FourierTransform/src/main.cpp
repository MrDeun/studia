#include "dft.h"
#include "fft.h"

#include <cassert>
#include <cstdio>
#include <iostream>
using std::vector;
using complex_d = std::complex<double>;
const double PI = acos(-1.0);

void show_complexs(const vector<complex_d> &points) {
  for (auto &point : points) {
    std::cout << point << std::endl;
  }
}

void transform_func(const vector<complex_d>& points){
  printf("y = ");
  for (int i=0;i<points.size();i++) {
    const char* format = "%fcos%dx + %fsin%dx + ";
    printf(format,points[i].real(),i,points[i].imag(),i);
  }
  puts("0");
}

std::vector<vector<complex_d>> input() {
  size_t tests_count;
  std::cin >> tests_count;
  std::vector<vector<complex_d>> tests(tests_count);
  for (auto &vec : tests) {
    size_t points_size;
    std::cin >> points_size;
    vector<complex_d> new_points(points_size);
    for (int i = 0; i < points_size; i++) {
      double x;
      std::cin >> x;
      complex_d temp{x, 0};
      new_points[i] = temp;
    }
    vec = new_points;
  }
  return tests;
}

int main() {
  vector<vector<complex_d>> test_cases = input();

  for (const auto& _case : test_cases) {
    vector<complex_d> fast_copied(_case), discrete_copied(_case);
    puts("### ORIGINAL VALUES ###");
    // show_complexs(_case);
    puts("### DISCRETE FOURIER TRANSFORM ###");
    discrete_fourier_transform(discrete_copied);
    // show_complexs(discrete_copied);
    // transform_func(discrete_copied);
    puts("### INVERSE DISCRETE FOURIER TRANSFORM ###");
    inverse_discrete_fourier_transform(discrete_copied);
    // show_complexs(discrete_copied);
    puts("#### FAST FOURIER TRANSFORM ###");
    fast_fourier_transform(fast_copied);
    // show_complexs(fast_copied);
    transform_func(fast_copied);
    puts("#### INVERSE FAST FOURIER TRANSFORM ###");
    inverse_fast_fourier_transform(fast_copied);
    // show_complexs(fast_copied);
  }
}
