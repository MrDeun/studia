#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <iterator>
#include <fstream>
#include <cstdint>


using BYTE = unsigned char;

std::vector<BYTE> vec_grip = {'G','R','I','P'};

std::vector<BYTE> read_content(const char* filename){
  std::ifstream file_stream(filename,std::ios::binary);
  file_stream.unsetf(std::ios::skipws);

  std::streampos file_size;
  file_stream.seekg(0,std::ios::end);
  file_size = file_stream.tellg();
  file_stream.seekg(0,std::ios::beg);

  std::cout << file_size << std::endl;

  std::vector<BYTE> vec;
  vec.reserve(file_size);
  vec.insert(vec.begin(),std::istream_iterator<char>(file_stream),std::istream_iterator<char>());
  return vec;
}

long convLong(std::vector<BYTE>::const_iterator it){
  uint8_t bytes[3] = {*it, *(it+1),*(it+2)};
  uint32_t number = 0;
  number = (bytes[0] << 16)|(bytes[1]<<8)|bytes[2];
  return number;
}

int main() {
  std::vector<BYTE> file_content = read_content("msg.bin");
  std::cout << file_content.size() << '\n';
  auto index = std::find(file_content.begin(), file_content.end(), vec_grip);

  std::cout << file_content[index]
            << file_content[index+1]
            << file_content[index+2]
            << file_content[index+3] << '\n';
  return 0; 
}
