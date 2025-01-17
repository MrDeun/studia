#ifndef METHANE
#define METHANE

#include<random>

  class CattleMethaneEvolution{
    private:
      std::random_device rd;
      std::mt19937 gen;



      int meat_caddle;
      int milk_caddle;
      int younglings;
    public:
      CattleMethaneEvolution():rd(),gen(rd()){
        
      }
  };

#endif