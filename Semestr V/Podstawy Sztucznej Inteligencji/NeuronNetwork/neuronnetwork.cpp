#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>

float learningCurve(float x, float learningCoeff){
    return (1-std::exp(-learningCoeff*x))/(1+std::exp(-learningCoeff*x));
}

std::vector<float> one = {
-1.0,-1.0,1.0,
-1.0,-1.0,1.0,
-1.0,-1.0,1.0,
-1.0,-1.0,1.0
};

std::vector<float> four = {
    1.0,-1.0,1.0,
    1.0,1.0,1.0,
    -1.0,-1.0,1
    -1.0,-1.0,1.0
};

int main(){
    float learningCoeff = 0.003;
    std::vector<float> coeff(one.size());
    std::fill(coeff.begin(),coeff.end(),0.0);
    float error=1.0;
    while(error>0.01){
        error = 0.0;
        float s = 0.0;
        for (int i=0;i<one.size();i++) {
            s += i*coeff[i];
        }
        float expected = learningCurve(s, 1.0);
        std::cout << "error: " << error << std::endl; 
    }
}