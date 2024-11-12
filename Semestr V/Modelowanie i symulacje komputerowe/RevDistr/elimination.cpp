#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
double genX() {
  return (double(rand()) / (RAND_MAX * 1.0)) * (8.0 - 4.0) - 4.0;
}

double genY() {
  return (double(rand()) / (RAND_MAX * 1.0)) * (6.0 / 4.0 - 0) - 0.0;
}

double Modify(double x){
  return 4.0*(pow(x,1.0/5.0)+1);
}

int main() {
  srand(time(nullptr));
  for (size_t i = 0; i < 1000;) {
    double x = Modify(genX());
    double y = genY();

    if (y > x)
      continue;
    else {
      printf("%f\n", x);
      i++;
    }
  }
}
