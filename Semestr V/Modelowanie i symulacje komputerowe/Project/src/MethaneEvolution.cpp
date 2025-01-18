#include "MethaneEvolution.h"

CattleMethaneEvolution::CattleMethaneEvolution(int starting_population)
    : rd(), gen(rd()), cowIsMilk(0.526), meat_caddle(0), milk_caddle(0),
      younglings(0), adultToYoung(7.0) {
  srand(starting_population * time(nullptr));
  for (int i = 0; i < starting_population; i++) {
    if (cowIsMilk(gen)) {
      milk_caddle++;
    } else {
      meat_caddle++;
    }

    younglings = (milk_caddle + meat_caddle) * adultToYoung(gen);

  }
}

void CattleMethaneEvolution::addAdult(){
  if(cowIsMilk(gen)){
    milk_caddle++;
  } else {
    meat_caddle++;
  }
}
