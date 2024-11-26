#include <ctime>
#include <random>
#include <cstdio>

std::mt19937 GEN(time(nullptr));

int main(){
	std::normal_distribution<> d{6.0,4.0};
	for(int i=0;i<10000;i++){
		printf("%f\n",d(GEN));
	}
}
