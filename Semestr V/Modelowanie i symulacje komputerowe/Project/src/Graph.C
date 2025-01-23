

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
void Graph(){
  std::array<int32_t, 5000> Values = {0};
  std::ifstream file_stream;
  file_stream.open("methane.data");

  int32_t tempVal;
  for (size_t i=0;i<5000;i++) {
    file_stream >> tempVal;
    Values[i] = tempVal;
    std::cerr << Values[i]<<'\n';
  }

  const int32_t maxValue = *std::max_element(Values.begin(),Values.end());
  const int32_t minValue = *std::min_element(Values.begin(),Values.end());
  fprintf(stderr,"Min: %d \t Max: %d\n",minValue,maxValue);

  
  TH1F* histograph = new TH1F("Values","Methane (kgs/year)",100,minValue-1,maxValue+1);
  for(size_t i=0;i<5000;i++){
    histograph->Fill(Values[i]);
  }
  histograph->Fit("expo");
  histograph->Draw();

}