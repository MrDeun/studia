#ifndef FFT 
#define FFT
#include <cmath>
#include <vector>
#include <complex>
using complex_d = std::complex<double>;
using std::vector;

void inverse_fast_fourier_transform(vector<complex_d> &points);
void fast_fourier_transform(vector<complex_d> &points);
void inverse_fast_fourier_transform(vector<complex_d> &points,int& count);
void fast_fourier_transform(vector<complex_d> &points, int& count);



#endif