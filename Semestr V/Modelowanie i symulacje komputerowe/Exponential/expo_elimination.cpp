#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
double ExpoDist(double x, double constant){
  return constant * std::exp(-constant * x);
}

double X(int max){
  return (double(rand()/(RAND_MAX*1.0))) * (double(max)) - 0.0;
}

double Y(double constant){
  return (double(rand()/(RAND_MAX*1.0))) * (double(constant)) - 0.0;
}

int main(){

  const double constant = 1.0;
  srand(time(nullptr));
  for (int i=0;i<2000;) {
    double check = ExpoDist(X(100000),constant);
    double _try = Y(constant);
    if (_try<=check){
      printf("%f\n",_try);
      i++;
    }
  }
}