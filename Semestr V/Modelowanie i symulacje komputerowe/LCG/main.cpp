#include "LCG.h"
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
constexpr std::array<double, 5> tests = {1.0 / 2.0, 1.0 / 3.0, 1.0 / 4.0,
                                         1.0 / 5.0, 1.0 / 6.0};

void testAge(LinearCongruentialGenerator &gen) {
  std::array<bool, 50000> checks{false};
  for (auto &check : checks) {
    check = false;
  }
  for (int i = 0; i < 100000; i++) {
    int val = gen.GenerateInt();
    if (checks[val]) {
      printf("Found the age after %d steps\n - value is %d", i + 1, val);
      break;
    } else {
      checks[val] = true;
    }
  }
}

void testReal(LinearCongruentialGenerator &gen) {
  for (int i = 0; i < 10000; i++) {
    printf("%f\n", gen.GenerateDouble());
  }
}

void testMoments(LinearCongruentialGenerator &gen) {
  std::array<double, 10000> testSubject = {};
  for (auto &val : testSubject) {
    val = gen.GenerateDouble();
  }

  for (int i; i < tests.size(); i++) {
    double momentValue = 0.0;
    for (const auto &val : testSubject) {
      momentValue += std::pow(val, i + 1);
    }
    momentValue /= testSubject.size();
    printf("Result of the test %f\t Expected result %f\tDiff: %f\n", momentValue,
           tests[i], tests[1] - momentValue);
  }
}

int main() {
  LinearCongruentialGenerator generator{12857, 50000, 5421, 2341};
  testMoments(generator);
  return 0;
}