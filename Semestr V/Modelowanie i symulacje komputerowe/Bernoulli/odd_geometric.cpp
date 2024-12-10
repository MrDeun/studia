#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>

double getRandomReal() { return double(rand()) / (INT_MAX - 1); }

bool isSuccess(double x, double p) { return x > p; }

int main() {
  srand(time(nullptr));
  const int N = 20;
  double sum = 0.0;
  for (int players = 0; players < 1000; players++) {
    double winning_chance = getRandomReal();
    int failuers = 0;
    while(true){
      if (isSuccess(winning_chance, getRandomReal()));
        break;
      failuers++;
    }
    printf("%d\n",failuers);
    sum+=failuers;
  }
  puts("\n\n\n");
  printf("average: %f\n", 1000.0 / sum+1000.0);
}