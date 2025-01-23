#include "MethaneEvolution.h"
#include <cstdint>
#include <cstdio>
#include <fstream>

void saveToFile(int* Values, size_t size_values){
  const char* filename = "methane.data";
  std::ofstream value_file(filename);
  for(int i=0;i<size_values;i++){
    value_file << Values[i]<<'\n';
  }
  return ;
}

int main(int, char **) {
  CattleMethaneEvolution subject;
  int32_t Values[5000] = {0};
  for (int i = 0; i < 5000; i++) {
    int32_t totalMethane = subject.Simulate(87205);
    Values[i] = totalMethane;
    // printf("%d\n",totalMethane);
    saveToFile(Values,5000);
  }
}