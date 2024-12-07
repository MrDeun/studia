#include "fft.h"
#include "regression.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

template<typename T>
using vec = std::vector<T>;

vec<vec<complex_d>> input() {
  size_t tests_count;
  std::cin >> tests_count;
  vec<vec<complex_d>> tests(tests_count);
  for (auto &_case : tests) {
    size_t points_size;
    std::cin >> points_size;
    vector<complex_d> new_points(points_size);
    for (int i = 0; i < points_size; i++) {
      double x;
      std::cin >> x;
      complex_d temp{double(i),x};
      new_points[i] = temp;
    }
    _case = new_points;
  }
  return tests;
}


int main(){
  vec<vec<complex_d>> test_cases = input();
  constexpr complex_d complex_zero{0.0,0.0};
  for(auto case_ : test_cases){
    fast_fourier_transform(case_);
    puts("real\timag");
    for (auto& coeff : case_) {
      if (abs(coeff) > 0.01) coeff = complex_zero;
      printf("%f\t%f\n",coeff.real(),coeff.imag());
    }
    inverse_fast_fourier_transform(case_);
    std::vector<double> X_s(case_.size());
    std::vector<double> Y_s(case_.size());
    for (int i=0;i<case_.size();i++) {
      X_s[i] = case_[i].real();
      Y_s[i] = case_[i].imag();
    }
    auto regress_result = linear_regression(X_s,Y_s);
    double coeff_d = regress_result.first;
    double constTerm = regress_result.second;
    printf("y = %fx + %f",coeff_d,constTerm); 
  }
}