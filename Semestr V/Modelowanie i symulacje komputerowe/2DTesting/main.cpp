#include "LCG.h"
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

void ChiSquareTest(std::vector<std::pair<double, double>> points,
                   size_t buckets) {
  double threshold = 1.0 / buckets;
  int bins[buckets][buckets] = {0};
  for (auto vec2 : points) {
    int x_index = vec2.first / threshold;
    int y_index = vec2.second / threshold;
    bins[x_index][y_index]++;
		// printf("bins[%d][%d] = %d\n",x_index,y_index,bins[x_index][y_index]);
		// printf("bins[%f][%f] = %d\n",vec2.first,vec2.second,bins[x_index][y_index]);
		// puts("");
  }
  int theoryBins[buckets][buckets];
  memset(theoryBins, 1, sizeof(theoryBins));
  double chiSquare = 0.0;
  int notEnoughs = 0;
  for (int i = 0; i < buckets; i++) {
    for (int j = 0; j < buckets; j++) {
      chiSquare += (double(std::pow(bins[i][j] - theoryBins[i][j], 2))) /
                   theoryBins[i][j];
      if (bins[i][j] < 1) {
        notEnoughs++;
      }
			printf("%d ",bins[i][j]);
    }
		puts("");
  }
  int degreeFree = buckets * buckets - 1 - notEnoughs;
  printf("X2 = %f, Degrees = %d", chiSquare, degreeFree);
}

void savePoints(const std::vector<std::pair<double,double>>& points, std::string filename){
	std::ofstream file(filename + ".txt");
	for (auto pair : points) {
		file << pair.first << '\n' << pair.second << '\n';
	}
	file.close();
}

int main() {
  LinearCongruentialGenerator generator{12857, 50000, 5421, 2341};
  std::array<double, 10000> numbers;
	for (auto& number : numbers) {
		number = generator.GenerateDouble();
	}
  std::vector<std::pair<double, double>> points1 = {};
  std::vector<std::pair<double, double>> points2 = {};

  for (int i = 0; i < numbers.size(); i += 2) {
    points1.push_back(std::make_pair(numbers[i], numbers[i + 1]));
  }

  for (int i = 0; i < numbers.size() - 1; i++) {
    points2.push_back(std::make_pair(numbers[i], numbers[i + 1]));
  }

  // printf("points1_size: %d\npoints2_size: %d\n",
  // points1.size(),points2.size());
  //ChiSquareTest(points1, 100);
	savePoints(points1, "points1");
	savePoints(points2, "points2");
}
