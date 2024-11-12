#include "LCG.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
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
  for (int i = 0; i < 1000; i++) {
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
    printf("Result of the test %f\t Expected result %f\tDiff: %f\n",
           momentValue, tests[i], tests[1] - momentValue);
  }
}

void testChiSquare(LinearCongruentialGenerator &gen, size_t binCount) {
  double threshold = (1.0 - 0.0) / binCount;
  std::vector<int> bins(binCount);
  for (int i = 0; i < 1000; i++) {
    int binIndex = (gen.GenerateDouble() - 0.0) / threshold;
    bins[binIndex]++;
  }
  std::vector<int> theoryBins(binCount);  
  std::fill(theoryBins.begin(),theoryBins.end(),1000/binCount);
  double chiSquare = 0.0;
  int notEnoughs = 0;
  for (int i = 0; i < binCount; i++) {
    chiSquare +=
        (double(std::pow(bins[i] - theoryBins[i],2))) / theoryBins[i];
    if (bins[i] < 5) {
      notEnoughs++;
    }
  }
  int degreeFree = binCount - 0 - 1 - notEnoughs;
  printf("ChiSquare: %f, Degree: %d",chiSquare,degreeFree);
}

int main() {
  LinearCongruentialGenerator generator{12857, 50000, 5421, 2341};
  testChiSquare(generator, 10);
  return 0;
}