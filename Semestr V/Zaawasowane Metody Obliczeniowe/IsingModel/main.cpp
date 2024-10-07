#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define POSITIVE 1
#define NEGATIVE -1

const size_t matSize = 40;

size_t getRandomIndex(size_t max) { return rand() % max; }

int *createNet(size_t size) { return new int[size * size]; }

void deleteNet(int *net) { delete[] net; }

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

int calculateBucketSteps(const size_t& size, const size_t& step) {
  int* mat = createNet(size);
  setWholeNet(mat,size,POSITIVE);
  int totalEnergy = -2 * calculateEnergy(mat,size);
  deleteNet(mat);
  return std::min(totalEnergy / step,20*step);
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

void bucketLoop(int *net, const size_t &size, int bucket,
                const int &iterations, const int &energyDelta) {
  int netEnergy = calculateEnergy(net, size);
  const int wholeEnergy = netEnergy + bucket;
  for (size_t i = 0; i < size; i++) {
    int &net_value = net[getRandomIndex(size) + size * getRandomIndex(size)];
    if (net_value == POSITIVE && bucket < energyDelta)
      continue;

    switch (net_value) {
    case POSITIVE:
      net_value = NEGATIVE;
      netEnergy += energyDelta;
      bucket -= energyDelta;
      break;
    case NEGATIVE:
      net_value = POSITIVE;
      netEnergy -= energyDelta;
      bucket += energyDelta;
      break;
    default:
      fprintf(stderr, "Error: expected -1 or 1, got %d\n", net_value);
      assert(false);
    }
    assert(netEnergy + bucket == wholeEnergy);
    printf("Value of bucket: %d\n", bucket);
  }
}

int main() {
  srand(time(NULL));
  fprintf(stderr, "POSITIVE: %d \nNEGATIVE: %d\n", POSITIVE, NEGATIVE);
  int energyDelta = testEnergy(matSize);
  size_t bucketCount = calculateBucketSteps(matSize,energyDelta);
  int *mat = createNet(matSize);
  for (int bucket = 0; bucket < bucketCount; bucket += energyDelta) {
    printf("Bucket Iteration no. %d\n",(bucket/energyDelta)+1);
    setWholeNet(mat, matSize, POSITIVE);
    bucketLoop(mat, matSize, bucket, 1000, energyDelta);
  }
  deleteNet(mat);
}