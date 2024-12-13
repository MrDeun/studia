#include "dft.h"

void discrete_fourier_transform(vector<complex_d> &points) {
  const auto points_size = points.size();
  vector<complex_d> transformed(points_size);
  for (int n = 0; n < points_size; n++) {
    complex_d c_n{};
    for (int i = 0; i < points_size; i++) {
      double angle = 2.0 * M_PI * n * i / points_size;
      c_n += points[i] * std::exp(complex_d(0.0, angle)); 
    }
    c_n /= points_size;
    transformed[n] = c_n;
  }
  points = transformed;
  return;
}

void inverse_discrete_fourier_transform(vector<complex_d> &points) {
  const auto points_size = points.size();
  vector<complex_d> transformed(points_size);
  for (int n = 0; n < points_size; n++) {
    complex_d c_n{};
    for (int i = 0; i < points_size; i++) {
      double angle = 2.0 * M_PI * n * i / points_size;
      c_n += points[i] * std::exp(complex_d(0.0, -angle));
    }
    //c_n /= points_size;
    transformed[n] = c_n;
  }
  points = transformed;
  return;
}

void discrete_fourier_transform(vector<complex_d> &points,int& count) {
  const auto points_size = points.size();
  vector<complex_d> transformed(points_size);
  for (int n = 0; n < points_size; n++) {
    complex_d c_n{};
    for (int i = 0; i < points_size; i++) {
      double angle = 2.0 * M_PI * n * i / points_size;
      c_n += points[i] * std::exp(complex_d(0.0, angle));
      count++;
    }
    c_n /= points_size;
    transformed[n] = c_n;
  }
  points = transformed;
  return;
}

void inverse_discrete_fourier_transform(vector<complex_d> &points,int& count) {
  const auto points_size = points.size();
  vector<complex_d> transformed(points_size);
  for (int n = 0; n < points_size; n++) {
    complex_d c_n{};
    for (int i = 0; i < points_size; i++) {
      double angle = 2.0 * M_PI * n * i / points_size;
      c_n += points[i] * std::exp(complex_d(0.0, -angle));
      count++;
    }
    //c_n /= points_size;
    transformed[n] = c_n;
  }
  points = transformed;
  return;
}

