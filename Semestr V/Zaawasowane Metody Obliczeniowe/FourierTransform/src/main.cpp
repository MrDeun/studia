#include "dft.h"
#include "fft.h"

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
using std::vector;
using complex_d = std::complex<double>;
const double PI = acos(-1.0);
constexpr complex_d complex_zero = 0.0 + 0.0j;
void show_complexs(const vector<complex_d> &points) {
  puts("x,y");
  for (auto &point : points) {
    printf("%f,%f\n",point.real(),point.imag());
  }
}

void transform_func(const vector<complex_d> &points) {
  printf("y = ");
  const char *format = "%fcos%dx + %fsin%dx + ";
  for (int i = 0; i < points.size(); i++) {
    printf(format, points[i].real(), i, points[i].imag(), i);
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

std::vector<vector<complex_d>> noisy_input() {
  size_t tests_count;
  std::cin >> tests_count;
  std::vector<vector<complex_d>> tests(tests_count);
  for (auto &vec : tests) {
    size_t points_size;
    std::cin >> points_size;
    // std::cerr << points_size;
    vector<complex_d> new_points(points_size);
    for (int i = 0; i < points_size; i++) {
      double x;
      std::cin >> x;
      complex_d temp{(double(i)*2.0*PI)/points_size, x};
      new_points[i] = temp;
    }
    vec = new_points;
  }
  return tests;
}

int main() {
  vector<vector<complex_d>> originalValues = input();

  for (const auto &_case : originalValues) {
    vector<complex_d> fast_copied(_case), discrete_copied(_case);
    // puts("### ORIGINAL VALUES ###");
    // show_complexs(_case);
    int count = 0;
    discrete_fourier_transform(discrete_copied,count);
    // printf("### DISCRETE FOURIER TRANSFORM: %d operations ###\n",count);
    // show_complexs(discrete_copied);
    // count = 0;
    inverse_discrete_fourier_transform(discrete_copied,count);
    // printf("### INVERSE DISCRETE FOURIER TRANSFORM: %d operations ###\n",count);
    // show_complexs(discrete_copied);
    count = 0;
    fast_fourier_transform(fast_copied,count);
    // printf("### FAST FOURIER TRANSFORM: %d operations ###\n",count);
    // show_complexs(fast_copied);
    count = 0;
    inverse_fast_fourier_transform(fast_copied,count);
    // printf("### INVERSE FAST FOURIER TRANSFORM: %d operations ###\n",count);
    // show_complexs(fast_copied);
  }

  vector<vector<complex_d>> noisyValues = input();
  assert(noisyValues.size() == originalValues.size());
  for (int i = 0; i < noisyValues.size(); i++) {
    assert(noisyValues[i].size() == originalValues[i].size());
    fast_fourier_transform(originalValues[i]);
    fast_fourier_transform(noisyValues[i]);
    for(int j=0;j<noisyValues[i].size();j++){
      noisyValues[i][j] -= originalValues[i][j]; 
    }
    // puts("COEFFICENTS");
    // show_complexs(noisyValues[i]);
    inverse_fast_fourier_transform(originalValues[i]);
    // puts("(X, Y)");
    inverse_fast_fourier_transform(noisyValues[i]);
    show_complexs(noisyValues[i]);

  }
}
