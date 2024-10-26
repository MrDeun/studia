#include "IsingModel.h"
#include "Statistics.h"

int main() {
  SimulationModel model(36,36);
  int pre = model.calculateEnergy();
  model.flipAll();
  int post = model.calculateEnergy();
  printf("Max energy: %d", post-pre);
  return 0;
}