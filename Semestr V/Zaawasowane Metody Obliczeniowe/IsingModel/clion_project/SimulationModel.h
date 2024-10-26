//
// Created by Patryk Michalak on 26.10.2024.
//

#ifndef SIMULATIONMODEL_H
#define SIMULATIONMODEL_H

#include <cstdint>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <bits/locale_classes.h>


class SimulationModel {
private:
    bool defaultState;
    const size_t width, height;
    std::vector<bool> Model;
    std::vector<int> bucketEnergies;
    double averageMagnetism;

    int8_t modelToVal(const bool& state) {
        return state ? 1 : -1;
    }

    size_t randomIndex() { return rand() % (width * height); }
    void flip(size_t index) { Model[index] = !Model[index]; }

    void reset();

public:
    int calculateEnergy();

    double calculateMagnet();

    void flipAll() {
        for (size_t i = 0; i < width * height; i++) {
            Model[i] = !Model[i];
        }
    }

    SimulationModel(size_t width, size_t height)
        : averageMagnetism(0.0), width(width), height(height), defaultState(true) {
        srand(time(nullptr));
        Model.reserve(width * height);
        std::fill(Model.begin(), Model.end(), true);
    }

    void Simulate(const size_t &iterations, int bucket);
};


#endif //SIMULATIONMODEL_H
