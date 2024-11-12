#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

using points = std::vector<double>;

void FourierTransform(points _points) {
  const size_t points_size = _points.size();
  for (size_t n = 1; n < points_size; n++) {
    double a_n = 0.0;
    double b_n = 0.0;
    for (size_t i = 0; i < points_size; i++) {
      a_n += _points[i] * std::sin(i * n * M_PI * 2 / points_size);
      b_n += _points[i] * std::cos(i * n * M_PI * 2 / points_size);
    }
    if (fabs(a_n) < 0.001) {
      a_n = 0.0;
    }
    if (fabs(b_n) < 0.001) {
      b_n = 0.0;
    }
    std::cout << a_n / points_size << "\t" << b_n / points_size << "\n";
  }
  std::cout << "\n\n\n\n\n";
}
std::vector<points> input() {
  size_t testCases;
  std::cin >> testCases;
  std::vector<points> vectorPoints(testCases);
  for (size_t i = 0; i < testCases; i++) {
    size_t pointCount;
    std::cin >> pointCount;
    points new_vec(pointCount);
    for (size_t j = 0; j < pointCount; j++) {
      double temp;
      std::cin >> temp;
      new_vec[j] = temp;
    }
    vectorPoints[i] = new_vec;
  }
  return vectorPoints;
}

void show_subjects(const std::vector<points>& _points) {
  for (const auto& testSubject : _points) {
    printf("Test subject: ");
    for (const auto& value : testSubject) {
      printf("%f ",value);
    }
    puts("");
  }
}

int main(int, char **) {
  std::cout << "Hello World\n";
  std::vector<points> subject = input();
  show_subjects(subject);
  FourierTransform(subject[0]);
}
