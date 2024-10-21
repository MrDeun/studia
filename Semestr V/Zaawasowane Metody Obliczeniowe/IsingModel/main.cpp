#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#define POSITIVE 1
#define NEGATIVE -1
#define comma ","

constexpr size_t matSize = 10;
constexpr int bucketNumbers[] = {100, 200, 250};

size_t getRandomIndex(const size_t &max) { return rand() % max; }

int *createNet(const size_t &size) { return new int[size * size]; }

void deleteNet(int *net) { delete[] net; net = nullptr;}

void setWholeNet(int *mat, size_t size, int value) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      mat[j + i * size] = value;
    }
  }
}

int calculateEnergy(int *net, size_t size) {
  int res = 0;
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      int x = (j + 1) % size;
      int y = (i + 1) % size;
      res += -(net[j + size * y] * net[j + size * i]);
      res += -(net[j + size * i] * net[x + size * i]);
      // printf("[%d][%d]: %d\n", i, j, res);
    }
  }
  return res;
}

float calculateMagnetize(int *net, size_t size) {
  int mag = 0;
  for (int y = 0; y < size; y++) {
    for (int x = 0; x < size; x++) {
      mag += net[x + size * y];
    }
  }
  return double(mag) / double(size * size);
}

int calculateBucketSteps(const size_t &size, const size_t &step) {
  int *mat = createNet(size);
  setWholeNet(mat, size, POSITIVE);
  int totalEnergy = -2 * calculateEnergy(mat, size);
  deleteNet(mat);
  return std::min(totalEnergy / step, 20 * step);
}

void printMat(int *mat, size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      printf("%d ", mat[j + size * i]);
    }
    puts("");
  }
}

int testEnergy(size_t size) {
  int *mat = createNet(size);
  setWholeNet(mat, size, POSITIVE);
  int firstTemp = calculateEnergy(mat, size);
  mat[0] = NEGATIVE;
  int secondTemp = calculateEnergy(mat, matSize);
  deleteNet(mat);
  fprintf(stderr, "Energy Delta: %d\n", secondTemp - firstTemp);
  return secondTemp - firstTemp;
}

void bucketLoop(int *net, const size_t &size, int bucket, const int &iterations,
                std::ofstream &streamfile) {
  const int wholeEnergy = calculateEnergy(net, size) + bucket;
  streamfile << "iteration,demonenergy,magnetize\n";
  streamfile << 0 << comma << bucket << comma << calculateMagnetize(net, size)
             << "\n";
  for (size_t i = 0; i < iterations; i++) {
    int &net_value = net[getRandomIndex(size) + size * getRandomIndex(size)];
    int preChange = calculateEnergy(net, size);
    net_value *= -1;
    int postChange = calculateEnergy(net, size);
    if (bucket + (preChange - postChange) < 0) {
      net_value *= -1;
    } else {
      bucket += (preChange - postChange);
    }
    assert(wholeEnergy == bucket + calculateEnergy(net, size));
    streamfile << i + 1 << comma << bucket << comma
               << calculateMagnetize(net, size) << "\n";
  }
}

void handleInput(size_t &size, size_t &iterations,
                 std::vector<int> &bucketNumbers) {
  std::cin >> size;
  std::cin >> size;
  std::cin >> iterations;
  size_t bSize;
  if (!bucketNumbers.empty()) {
    bucketNumbers.clear();
  }
  std::cin >> bSize;
  for (int i = 0; i < bSize; i++) {
    int temp;
    std::cin >> temp;
    bucketNumbers.push_back(temp);
  }
}

int main() {
  srand(time(NULL));
  size_t size{}, iterations{};
  std::vector<int> bucketNumbers;
  handleInput(size,  iterations, bucketNumbers);
  fprintf(stderr, "POSITIVE: %d \nNEGATIVE: %d\n", POSITIVE, NEGATIVE);
  // int energyDelta = testEnergy(matSize);
  // size_t bucketCount = calculateBucketSteps(matSize,energyDelta);
  int *mat = createNet(size);
  for (int i = 0; i < bucketNumbers.size(); i++) {
    char filename[256];
    sprintf(filename, "test_outputs/net%d.csv", i + 1);
    std::ofstream test_file(filename);
    int bucket = bucketNumbers[i];
    setWholeNet(mat, matSize, POSITIVE);
    bucketLoop(mat, matSize, bucket, iterations, test_file);
  }
  // fprintf(stderr,"Bucket Iteration no. %d\n",(bucket/energyDelta)+1);
  deleteNet(mat);
}