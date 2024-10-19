#include "isingmodel.hpp"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

std::vector<int> input(size_t& width, size_t& height, size_t& iterations){
  std::cin >> width >> height >> iterations;
  size_t temp;
  std::cin >> temp;
  std::vector<int> vec(temp);
  assert(temp == vec.size());
  for (auto& bucket : vec) {
    std::cin >> temp;
    bucket = temp;
  }
  return vec;
}

size_t get_rand_index(const size_t& max) {
  return rand()%max;
}

void write_log(std::ofstream& file, int bucket, double mag, size_t iteration){
  char buf[1024];
  sprintf(buf,"%u\t%d\t%f\n",iteration,bucket,mag);
  file << buf;
}

void bucketLoop(IsingModel& net, size_t& iterations, int& bucket, std::ofstream& file){
  const int totalEnergy = bucket + net.calculateTemp();
  write_log(file,bucket, net.calculateMag(), 0);
  for (size_t i=0;i<iterations;i++) {
    size_t random_index = get_rand_index(net.size());
    int preChange = net.calculateTemp();
    net.flip(random_index);
    int postChange = net.calculateTemp();
    int delta = postChange - preChange;
    printf("\n\n%d\n\n",delta);
    assert(false);
  }
}

int main() {
  srand(time(nullptr));
  size_t width, height, iterations;
  std::vector<int> buckets = input(width,height,iterations);
  char path[256];
  IsingModel net(width,height);
  for(int i =0;i<buckets.size();i++){
    net.set_all(1);
    sprintf(path, "test_outputs/bucket%d.out",i+1);
    std::ofstream file(path);
    bucketLoop(net,iterations,buckets[i],file);
  }
}