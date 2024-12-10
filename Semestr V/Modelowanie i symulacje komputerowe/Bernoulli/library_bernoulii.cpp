#include <random>

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution bern_dist(0.4);
  for(int i=0;i<1000;i++){
    int success = 0;
    for (int chance = 0;chance<20;chance++){
      auto odd = bern_dist(gen);
      if (odd)
        success++;
    }
    printf("%d\n",success);
  }
}