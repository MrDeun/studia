#include "MethaneEvolution.h"
#include <cstdint>
#include <random>

CattleMethaneEvolution::CattleMethaneEvolution()
    : rd(), gen(rd()), cowIsMilk(), meat_caddle(0), milk_caddle(0),
      younglings(0), adultToYoung(7.0),birthRate(0.1) {
    cowIsMilk.param(std::bernoulli_distribution::param_type(0.526));    
    methaneModifier.param(std::uniform_real_distribution<>::param_type(0.8,1.2));
    milkDeathRatio.param(std::bernoulli_distribution::param_type(0.25));
    meatDeathRatio.param(std::bernoulli_distribution::param_type(0.3));
    avgMethPerHead_Index.param(std::discrete_distribution<>::param_type({15,20,30,20,15}));

}



void CattleMethaneEvolution::init(int starting_population){
    younglings = 0;
    meat_caddle = 0;
    milk_caddle = 0;
    
    for (int i = 0; i < starting_population; i++) {
      addAdult();
    }
    younglings = (milk_caddle + meat_caddle) * adultToYoung(gen);
}

void CattleMethaneEvolution::newGenerationCattle(){
  int i;
  const int32_t youngling_copy = younglings;
  for(i=0;i<youngling_copy;i++){
    if (adultHoodAchieved(gen)) {
      addAdult();
      younglings--;
    }
  }

  const auto allAdults = meat_caddle + milk_caddle;
  for (i=0; i<allAdults/2; i++) {
    if (birthRate(gen)) {
      younglings++;
    }
  }
  
}

void CattleMethaneEvolution::deathOfCattle(){
  int i;
  for (i=0;i<meat_caddle;i++) {
    if(meatDeathRatio(gen)){
      meat_caddle--;
    }
  }
  for (i=0;i<milk_caddle;i++) {
    if (milkDeathRatio(gen)) {
      milk_caddle--;
    }
  }
}

int32_t CattleMethaneEvolution::methaneInMonth(int month){
  int32_t totalMethane = 0;
  for(int i=0;i<milk_caddle;i++) {
    totalMethane += methaneModifier(gen)*1.1*averageMethanePerHead[avgMethPerHead_Index(gen)];
  }
  for(int i=0;i<meat_caddle;i++) {
    totalMethane += methaneModifier(gen)*0.9*averageMethanePerHead[avgMethPerHead_Index(gen)];
  }
  for(int i=0;i<younglings;i++) {
    totalMethane += methaneModifier(gen)*0.4*averageMethanePerHead[avgMethPerHead_Index(gen)];
  }

  return totalMethane*(1.0+seasonModifier[month]);
}


int32_t CattleMethaneEvolution::Simulate(int starting_population){
  init(starting_population);
  int32_t methane_kgs = 0;
  for (int i=0;i<12;i++) {
    newGenerationCattle();
    deathOfCattle();
    methane_kgs += methaneInMonth(i);
  }
  return methane_kgs;
}

void CattleMethaneEvolution::addAdult(){
  if(cowIsMilk(gen)){
    milk_caddle++;
  } else {
    meat_caddle++;
  }
}
