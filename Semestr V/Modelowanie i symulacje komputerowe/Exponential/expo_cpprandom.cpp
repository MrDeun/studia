#include <random>
#include <cstdio>

int main(){
  std::random_device rd;
  std::mt19937 gen(rd());

  std::exponential_distribution<> expo_dist(1);

  for(int i=0;i<1000;i++) {
    printf("%f\n",expo_dist(gen));
  }
}
