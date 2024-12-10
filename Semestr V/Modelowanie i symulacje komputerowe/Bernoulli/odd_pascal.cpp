#include <climits>
#include <cstdio>
#include <cstdlib>
#include <ctime>

double getRandomReal() { return double(rand()) / (INT_MAX - 1); }

bool isSuccess(double x, double p) { return x > p; }

int main() {
  srand(time(nullptr));
  double sum = 0.0;
  for(int i=0;i<1000;i++){
    double winning_chance = getRandomReal();
    int failuers = 0;
    int success = 0;
    while(true) {
      isSuccess(winning_chance,getRandomReal()) ? success++ : failuers++;
      if (failuers > 5){
        break;
      }
    }
    printf("%d\n",success);
    sum+=success;
  }
  puts("\n\n\n");
  printf("average: %f\n", sum / 1000);
}