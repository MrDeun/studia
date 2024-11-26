#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <numeric>
constexpr int iterations = 8;

double uniform_linear(){
  return double(rand())/RAND_MAX;
}

double central_normal(double mean, double stddev){
  std::array<double,iterations> arr;
  for (int i=0;i<iterations;i++) {
    arr[i] = uniform_linear();
    //fprintf(stderr,"%f\t",arr[i]);
  }
  // fprintf(stderr,"\n");
  const double sum = std::reduce(arr.begin(),arr.end(),0.0,std::plus{});
  fprintf(stderr,"%f\n",sum);
  const double top = ((1.0/iterations) * sum) - mean;
  const double bottom = stddev / std::sqrt(iterations);
  return top/bottom;
}

int main(){
  srand(time(nullptr));
  for (int i=0;i<10000;i++) {
    printf("%f\n",central_normal(0.5,1.0/12.0));
  }

}