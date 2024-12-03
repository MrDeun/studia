#include <cstdio>
#include <cstdlib>
constexpr int results[] = {0,1,2,3,4};
constexpr double chance[] = {0.25,0.15,0.2,0.1,0.3};
constexpr int result_size = sizeof(results)/sizeof(int);

double getRandomReal(){
    return double(rand())/(RAND_MAX-1);
}

double getIndex(){
    return rand()%result_size;
}

int main(){
    for (int i=0;i<10000;) {
        double r = getRandomReal();
        int index = getIndex();
        if (r <= chance[index]) {
            printf("%d\n",results[index]);
            i++;
        }

    }
}
