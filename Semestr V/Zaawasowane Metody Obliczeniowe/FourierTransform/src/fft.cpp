#include "fft.h"
#include <cmath>

void fast_fourier_transform(vector<complex_d> &points,int& count) {
  const size_t points_size = points.size();
  if (points_size == 1)
    return;

  vector<complex_d> first_half(points_size / 2), second_half(points_size / 2);
  for (int i = 0; 2 * i < points_size; i++) {
    first_half[i] = points[2 * i];
    second_half[i] = points[2 * i + 1];
  }
  fast_fourier_transform(first_half,count);
  fast_fourier_transform(second_half,count);

  double ang = 2 * M_PI / points_size * 1.0f;
  complex_d w(1.0f), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < points_size; i++) {
    points[i] = first_half[i] + w * second_half[i];
    points[i + points_size / 2] = first_half[i] - w * second_half[i];
    count+=2;
    points[i] /= 2.0;
    points[i + points_size/2] /= 2.0;
    w *= wn;
  }

}
void inverse_fast_fourier_transform(vector<complex_d> &points,int& count) {
  const size_t points_size = points.size();
  if (points_size == 1)
    return;

  vector<complex_d> first_half(points_size / 2), second_half(points_size / 2);
  for (int i = 0; 2 * i < points_size; i++) {
    first_half[i] = points[2 * i];
    second_half[i] = points[2 * i + 1];
  }
  inverse_fast_fourier_transform(first_half,count);
  inverse_fast_fourier_transform(second_half,count);

  double ang = 2 * M_PI / points_size * -1.0f;
  complex_d w(1.0f), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < points_size; i++) {
    points[i] = first_half[i] + w * second_half[i] ;
    points[i + points_size / 2] = first_half[i] - w * second_half[i];
    count+=2;
    w *= wn;
  }
}

void fast_fourier_transform(vector<complex_d> &points) {
  const size_t points_size = points.size();
  if (points_size == 1)
    return;

  vector<complex_d> first_half(points_size / 2), second_half(points_size / 2);
  for (int i = 0; 2 * i < points_size; i++) {
    first_half[i] = points[2 * i];
    second_half[i] = points[2 * i + 1];
  }
  fast_fourier_transform(first_half);
  fast_fourier_transform(second_half);

  double ang = 2 * M_PI / points_size * 1.0f;
  complex_d w(1.0f), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < points_size; i++) {
    points[i] = first_half[i] + w * second_half[i];
    points[i + points_size / 2] = first_half[i] - w * second_half[i];
    points[i] /= 2.0;
    points[i + points_size/2] /= 2.0 ;
    w *= wn;
  }

}
void inverse_fast_fourier_transform(vector<complex_d> &points) {
  const size_t points_size = points.size();
  if (points_size == 1)
    return;

  vector<complex_d> first_half(points_size / 2), second_half(points_size / 2);
  for (int i = 0; 2 * i < points_size; i++) {
    first_half[i] = points[2 * i];
    second_half[i] = points[2 * i + 1];
  }
  inverse_fast_fourier_transform(first_half);
  inverse_fast_fourier_transform(second_half);

  double ang = 2 * M_PI / points_size * -1.0f;
  complex_d w(1.0f), wn(cos(ang), sin(ang));
  for (int i = 0; 2 * i < points_size; i++) {
    points[i] = first_half[i] + w * second_half[i] ;
    points[i + points_size / 2] = first_half[i] - w * second_half[i];
    w *= wn;
  }
}