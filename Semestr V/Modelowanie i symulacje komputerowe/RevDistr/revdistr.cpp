#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>

double GenerateDouble(){
  return double(rand())/RAND_MAX;
}

double Modify(double x){
  return 4.0*(std::pow(x,1.0/6.0)+1);
}

int main(){
  srand(time(nullptr));
  for (size_t i = 0; i < 1000; i++) {
    double genRan = GenerateDouble();
    printf("%f\n",Modify(genRan));
  }
}
