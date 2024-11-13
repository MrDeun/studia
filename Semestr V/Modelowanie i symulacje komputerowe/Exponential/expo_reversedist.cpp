#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

double Dist(){
  return double(rand())/RAND_MAX;
}

double Modify(double x, double constant){
  return -1.0/constant * std::log(1-x);
}

int main(){
  srand(time(nullptr));
  for (int i=0;i<2000;i++) {
    printf("%f\n",Modify(Dist(), 1.0));
  }
}