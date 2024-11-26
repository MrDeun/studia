#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

bool _switch = false;

double rand_linear(){
  return double(rand())/(RAND_MAX-1);  
}

double box_miller_normaldist(double mean, double stddev){
  double u1 = rand_linear();
  double u2 = rand_linear();
  double R = std::sqrt(-2.0*std::log(u1));
  double theta = 2*M_PI*u2;
  
  double result;
  if (_switch) {
    result = R*std::sin(theta);
  } else {
    result = R*std::cos(theta);
  }
  fprintf(stderr, "theta: %f\tR: %f\tresult: %f\t",theta,R,result);
  _switch = !_switch;
  return result*stddev + mean;
}

int main(){
  srand(time(nullptr));
  for(int i=0;i<10000;i++){
    printf("%f\n",box_miller_normaldist(6.0,4.0));
  }
}