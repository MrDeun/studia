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
    int success = 0;
    for (int i = 0; i < N; i++) {
      isSuccess(winning_chance,getRandomReal()) ? success++ : failuers++;
    }
    printf("%d\n",success);
    sum+=success;
  }
  puts("\n\n\n");
  printf("average: %f\n", sum / 1000);
}