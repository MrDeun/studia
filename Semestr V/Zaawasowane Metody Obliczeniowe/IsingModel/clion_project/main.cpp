#include <iostream>
#include "SimulationModel.h"

int main() {
    SimulationModel model(36,36);
    int pre_change = model.calculateEnergy();
    model.flipAll();
    int post_change = model.calculateEnergy();
    printf("PreChange: %d\nPostChange: %d\nDelta: %d", pre_change,post_change,post_change-pre_change);
    return 0;
}
