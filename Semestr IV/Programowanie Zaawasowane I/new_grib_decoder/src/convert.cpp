//
// Created by Patryk on 24-Apr-24.
//

#include "convert.h"
#include <cstdint>
#include <vector>

uint8_t convert::to_byte(std::vector<uint8_t>::iterator index) {
  uint8_t half_two = (*index);
  return half_two;
}

uint32_t convert::to_size(std::vector<uint8_t>::iterator index) {
  uint8_t bytes[] = {*index, *(index + 1), *(index + 2)};
  uint32_t size = 0;
  size = bytes[0] << 16 | bytes[1] << 8 | bytes[2];
  return size;
}

uint16_t convert::to_short(std::vector<uint8_t>::iterator index) {
  uint8_t bytes[] = {*(index), *(index + 1)};
  uint16_t result = bytes[1] << 8 | bytes[0];
  return result;
}

float convert::to_float3(std::vector<uint8_t>::iterator index) {
  int32_t byte_size = to_size(index);
  int8_t* ptr_bytes = (int8_t*)&byte_size;
  if (ptr_bytes[1] > 127){
    ptr_bytes[1] << 1;
    ptr_bytes[1] >> 1;
    byte_size *= -1;
    byte_size ++;
  }

  return (float)byte_size;
}

float convert::to_float(std::vector<uint8_t>::iterator index) {
  uint8_t bytes[] = {*index, *(index + 1), *(index + 2), *(index + 3)};
  float result = 0;
  result = bytes[3] << 24 | bytes[2] << 16 | bytes[1] << 8 | bytes[0];
  return result;
}

uint32_t convert::to_long(std::vector<uint8_t>::iterator index) {
  uint8_t bytes[] = {*index, *(index + 1), *(index + 2), *(index + 3)};
  uint32_t result = bytes[3] << 24 | bytes[2] << 16 | bytes[1] << 8 | bytes[0];
  return result;
}