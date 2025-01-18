#ifndef METHANE
#define METHANE

#include <cstdlib>
#include <ctime>
#include <random>

class CattleMethaneEvolution {
private:
  std::random_device rd;
  std::mt19937 gen;

  std::bernoulli_distribution cowIsMilk;
  std::exponential_distribution<> adultToYoung;

  void addAdult();


  int meat_caddle; // in thousands
  int milk_caddle; // in thousands
  int younglings;  // in thousands
public:
  CattleMethaneEvolution(int starting_population);
  
};

#endif