

#include <cstdio>
#include <random>
int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::geometric_distribution<> dist{0.4};
  double sum = 0.0;
  for (int i = 0; i < 1000; i++) {
    int failures = 0;
    while (true) {
      if (dist(gen)) {
        break;
      }
      failures++;
    }
    printf("%d\n",failures);
  }
  puts("\n\n\n\n\n\n\n");
  printf("%f\n",sum/1000.0);
}