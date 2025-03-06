#ifndef METHANE
#define METHANE

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <random>

class CattleMethaneEvolution {
private:
  std::random_device rd;
  std::mt19937 gen;

  std::bernoulli_distribution cowIsMilk;
  std::bernoulli_distribution adultHoodAchieved;
  std::bernoulli_distribution birthRate;
  std::bernoulli_distribution milkDeathRatio;
  std::bernoulli_distribution meatDeathRatio;
  
  std::discrete_distribution<> avgMethPerHead_Index;
  std::exponential_distribution<> adultToYoung;
  std::uniform_real_distribution<> methaneModifier;

  // seasonModifier = 3.2*normalDist(X:mean=6,stddev=2.4)-0.2
  inline static const float seasonModifier[12] = {
      -0.13927, -0.067,  0.0435, 0.17588, 0.28769,  0.33192,
      0.28769,  0.17588, 0.0435, -0.67,   -0.13927, -0.1766};

  inline static const float averageMethanePerHead[5] = {
      81.1 / 12.0, 87.31 / 12.0, 99.28 / 12.0, 102.7 / 12.0, 112.7 / 12.0,
  };

  void init(int);

  void addAdult();
  void newGenerationCattle();
  void deathOfCattle();
  int32_t methaneInMonth(int);

  int meat_caddle;  
  int milk_caddle;  
  int younglings;   

public:
  CattleMethaneEvolution();
  int32_t Simulate(int starting_population);
};

#endif