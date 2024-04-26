#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using byte_vector = std::vector<uint8_t>;

namespace convert {
/*float to_float(byte_vector::const_iterator first_byte_ptr) {
  float result;
  return result;
}

int32_t to_long(byte_vector::const_iterator first_byte_ptr) {
  int32_t result;
  return result;
}*/

uint32_t read_size(byte_vector::const_iterator first_byte_ptr) {
  uint8_t bytes[3] = {*first_byte_ptr, *(first_byte_ptr + 1),
                      *(first_byte_ptr + 2)};
  uint32_t result = 0;
  result = bytes[2] << 16 | bytes[1] << 8 | bytes[0];
  return result;
}
}; // namespace convert

template <class T>
void operator<<(std::ostream &output, std::vector<T> &vec_in) {
  output << "{";
  for (T element : vec_in) {
    output << " ," << element;
  }
  output << " }";
  return;
}

byte_vector vec_grip = {'G', 'R', 'I', 'P'};

byte_vector read_content(const char *filename) {
  std::ifstream file_stream(filename, std::ios::binary);
  file_stream.unsetf(std::ios::skipws);

  std::streampos file_size;
  file_stream.seekg(0, std::ios::end);
  file_size = file_stream.tellg();
  file_stream.seekg(0, std::ios::beg);

  std::cout << file_size << std::endl;

  byte_vector vec;
  vec.reserve(file_size);
  vec.insert(vec.begin(), std::istream_iterator<char>(file_stream),
             std::istream_iterator<char>());
  return vec;
}

void handle_PSG_msg(byte_vector PDS_msg, bool &GDS_flag, bool &BMS_flag) {
  uint8_t current_byte = PDS_msg[4];
  switch (current_byte) {
  case 0b00000011:
    GDS_flag = true;
    BMS_flag = true;
    return;
  case 0b00000001:
    GDS_flag = true;
    BMS_flag = false;
    return;
  case 0b00000010:
    GDS_flag = false;
    BMS_flag = true;
    return;
  default:
    GDS_flag = false;
    BMS_flag = false;
    return;
  }
}

byte_vector read_from_content(byte_vector::const_iterator it,
                              uint32_t msg_size) {
  byte_vector msg = {};
  for (size_t i = 0; i < msg_size; i++) {
    msg.push_back(*it);
    it++;
  }
  return msg;
}

int main() {
  byte_vector file_content = read_content("msg.bin");
  byte_vector::iterator index =
      std::search(file_content.begin(), file_content.end(), vec_grip.begin(),
                  vec_grip.end());
  index += 3;
  uint32_t IS_msg_size = convert::read_size(index);
  std::cout << IS_msg_size;
  index += 4;
  byte_vector IS_msg = read_from_content(index, IS_msg_size);
  index += IS_msg_size;
  uint32_t PDS_msg_size = convert::read_size(index);
  index += 3;
  byte_vector PDS_msg = read_from_content(index, PDS_msg_size);
  bool GDS_flag, BMS_flag;
  handle_PSG_msg(PDS_msg, GDS_flag, BMS_flag);
  return 0;
}
