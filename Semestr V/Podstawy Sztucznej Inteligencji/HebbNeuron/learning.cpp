#include <algorithm>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

void TestP(const vector<double>& weights, const vector<vector<int>>& TestVector, const vector<int>& t, int idx) {

    double x = 0;
    double y = 0;
    for (int i = 0; i < TestVector[idx].size(); i++) {
        x += TestVector[idx][i] * weights[i];
    }
    y = 1. / (1. + exp(-x));

    //cout << "TEST DLA " << t[idx] << "  " << y << endl;
}

void Learn(const vector<vector<int>>& p, int Cmax, double Emax, double learning_rate, const vector<int>& t, const vector<vector<int>>& testp) {

    mt19937 rng(random_device{}());
    uniform_real_distribution<double> dist(-1.0, 1.0);
    vector<double> weights;
    // Inicjalizacja wag
    for (int q = 0; q < p[0].size(); q++) {
        weights.push_back(dist(rng));
    }


    int c = 0; // licznik epok

    while (c < Cmax) {
        double E = 0; // Error

        std::vector<int> order = { 0, 1 };
        std::random_shuffle(order.begin(),order.end());
        for (int q = 0; q < 2; q++) {

            int obrazP = order[q];
            double x = 0;

            for (int i = 0; i < p[obrazP].size(); i++) {
                x += p[obrazP][i] * weights[i];
            }

            double y = 1. / (1. + exp(-x)); //sigmoidalna

            //wagi
            for (int i = 0; i < weights.size(); i++) {
                weights[i] = weights[i] + learning_rate * (t[obrazP] - y) * y * (1 - y) * p[obrazP][i];
            }

            //błąd
            E += pow(t[obrazP] - y, 2) / 2;
        }

        c++; // epoka++
        std::cout << E << std::endl;
        if (E < Emax) {
            break;
        }
    }

    TestP(weights, testp, t, 0);
    TestP(weights, testp, t, 1);
    weights.clear();
}

int main() {
    vector<vector<int>> p = { {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1}, // p1 = A
        {
        1, 1, 1, 1, 1,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1} // p2 = C
    };


    vector<vector<int>> testp = { {
        1, 1, 1, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 0,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1,
        1, 0, 0, 0, 1}, // testp1 = A
        {
        1, 1, 1, 0, 1,
        1, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 0, 0, 0, 0,
        1, 1, 1, 1, 1} // testp2 = C
    };

    //OCZEKIWANE WARTOŚCI
    vector<int> t = { 0, 1 };
    // p1 == 0 ; A
    // p2 == 1 ; C

    double learning_rate = 0.001;
    double Emax = 0.01; // error
    int Cmax = 20000; // epochs

    cout << "Przeprowadzone jest 10 testow uczenia dla litery A oraz C w celu sprawdzenia poprawnosci dzialania programu" << endl;

    for (int i = 0; i < 10; i++) {
        int testnum = i + 1;
        //cout << "test nr: " << testnum << endl;
        Learn(p, Cmax, Emax, learning_rate, t, testp);
        //cout << endl;
    }

    cout << endl;



    return 0;
}