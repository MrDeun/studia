#ifndef DFF 
#define DFF
#include <vector>
#include <complex>
using complex_d = std::complex<double>;
using std::vector;

void discrete_fourier_transform(vector<complex_d>& _points);
void inverse_discrete_fourier_transform(vector<complex_d> &_points);
void discrete_fourier_transform(vector<complex_d>& _points, int& count);
void inverse_discrete_fourier_transform(vector<complex_d> &_points, int& count);

#endif