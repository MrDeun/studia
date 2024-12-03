#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
double getRandomReal(){
    return double(rand())/(RAND_MAX-1);
}

int discrete_distribution(){
    double D = getRandomReal();
    if (D<=0.25){
        return 0;
    } else if (D>0.25 && D<=0.40) {
        return 1;
    } else if (D>0.40 && D<=0.60) {
        return 2;
    } else if (D>0.60 && D<=0.70) {
        return 3;
    } else if (D>0.70 && D<=1.0){
        return 4;
    }

    assert(D<=1.0 && D>=0.0);
    return 0.0;
}

int main(){
    srand(time(nullptr));
    for(int i=0;i<10000;i++){
        printf("%d\n",discrete_distribution());
    }
}
