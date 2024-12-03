#include<random>
#include<cstdio>


int main(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::discrete_distribution<> dist({25,15,20,10,30});
  for(int i=0;i<1e4;i++){
    printf("%d\n",dist(gen));
  }
  return 0;
}