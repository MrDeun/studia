#include "IsingModel.h"
#include <numeric>

double SimulationModel::calculateMagnet() {
    int magnet = std::reduce(Model.begin(), Model.end(), 0, std::plus{});
    return double(magnet) / double(width * height);
}

int SimulationModel::calculateEnergy() {
    int res = 0;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            size_t next_x = (x + 1) % width;
            size_t next_y = (y + 1) % height;

            res += -(Model[x + width * y] * Model[next_x + width * y]);
            res += -(Model[x + width * y] * Model[x + width * next_y]);
        }
    }
}

void SimulationModel::Simulate(size_t iterations, int bucket) {
    const int totalEnergy = bucket + calculateEnergy();
    double Magnetism = 0.0;
    for (int i = 0; i < iterations; i++) {
        size_t index = randomIndex();
        bucketEnergies.push_back(bucket);
        int preChange = calculateEnergy();
        Magnetism += (calculateMagnet());
        flip(index);
        int postChange = calculateEnergy();
        int diff = postChange - preChange;
        if (diff < 0 && bucket + diff < 0) {
            flip(index);
        } else {
            bucket += diff;
        }
    }
    averageMagnetism = Magnetism / iterations;
    reset();
}

void SimulationModel::reset() {
    bucketEnergies.clear();
    averageMagnetism = 0.0;
    defaultState = true;
    std::fill(Model.begin(), Model.end(), 1);
}
