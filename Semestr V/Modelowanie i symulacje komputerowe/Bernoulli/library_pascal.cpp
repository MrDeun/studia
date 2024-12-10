#include <cstdio>
#include <random>

int main(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::negative_binomial_distribution<> dist(5,0.6);
  double sum=0;
  for (int i=0;i<1000;i++) {
    int odd = dist(gen);
    printf("%d\n",odd);
    sum += odd;
  }
  puts("\n\n\n\n\n\n");
  printf("%f\t",sum/1000.0);
}