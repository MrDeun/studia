//
// Created by Patryk Michalak on 26.10.2024.
//

#include "SimulationModel.h"

#include <cassert>
#include <numeric>

double SimulationModel::calculateMagnet() {
    const int magnet = std::reduce(Model.begin(), Model.end(), 0, std::plus{});
    return double(magnet) / double(width * height);
}

int SimulationModel::calculateEnergy() {
    int res = 0;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t next_x = (x + 1) % width;
            size_t next_y = (y + 1) % height;

            res += -(modelToVal(Model[x + width * y]) * modelToVal(Model[next_x + width * y]));
            res += -(modelToVal(Model[x + width * y] * modelToVal(Model[x + width * next_y])));
        }
    }
    return res;
}

void SimulationModel::Simulate(const size_t &iterations, int bucket) {
    const int totalEnergy = bucket + calculateEnergy();
    double Magnetism = 0.0;
    for (int i = 0; i < iterations; i++) {
        const size_t index = randomIndex();
        bucketEnergies.push_back(bucket);
        const int preChange = calculateEnergy();
        flip(index);
        const int postChange = calculateEnergy();
        const int diff = postChange - preChange;
        if (diff < 0 && bucket + diff < 0) {
            flip(index);
        } else {
            bucket += diff;
        }
        Magnetism += (calculateMagnet());
        assert(totalEnergy == bucket + calculateEnergy());
    }
    averageMagnetism = Magnetism / double(iterations);
    reset();
}

void SimulationModel::reset() {
    bucketEnergies.clear();
    averageMagnetism = 0.0;
    defaultState = true;
    std::fill(Model.begin(), Model.end(), true);
}
