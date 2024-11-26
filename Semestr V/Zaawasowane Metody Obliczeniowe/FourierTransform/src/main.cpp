#include <complex>
#include <cstdio>
#include <iostream>
#include <vector>
using points_t = std::vector<std::complex<float>>;

float get_x(int iteration, int max){
  return (double(iteration)/max)*2.0f*M_PI;
}

void discrete_fourier_transform(points_t _points){
  const auto _points_size = _points.size(); 
  for(int n=1;n<_points_size;n++){
    std::complex<float> c_n{};
    for (int i=0;i<_points_size;i++) {
      c_n += std::polar(std::abs(_points[i]),get_x(i, _points_size)*n);
    }
    printf("real:%f\timag%f\n",c_n.real()/_points_size,c_n.imag()/_points_size);
  }
  return;  
}
void fast_fourier_transform(points_t _points);
void inverse_fast_fourier_transform(points_t _points);
void inverse_discrete_fourier_transform(points_t _points);

std::vector<points_t> input(){
  size_t tests_count; 
  std::cin >> tests_count;
  std::vector<points_t> tests(tests_count);
  for (auto& vec : tests) {
    size_t points_size;
    std::cin >> points_size;
    points_t new_points(points_size);
    for (int i=0;i<points_size;i++) {
      float x = get_x(i,points_size);
      float y;
      std::cin >> y;
      new_points[i] = std::complex<float>{x,y};
    }
    vec = new_points;
  }
  return tests;
}

int main(){
  std::vector<points_t> test_cases = input();
  for (auto points : test_cases) {
    discrete_fourier_transform(points);
  }
}
















