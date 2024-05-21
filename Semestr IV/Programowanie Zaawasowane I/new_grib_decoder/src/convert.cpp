//
// Created by Patryk on 24-Apr-24.
//

#include "convert.h"

uint16_t convert::to_byte(std::vector<uint8_t>::iterator index){
    uint16_t half_two = 0;
    half_two = 0x00 << 8 | (*index);
    return half_two;
}

uint32_t convert::to_size(std::vector<uint8_t>::iterator index) {
    uint8_t bytes[] = {*index,*(index+1),*(index+2)};
    uint32_t size = 0;
    size = bytes[2] << 16 | bytes[1] << 8 | bytes[0];
    return  size;
}

int16_t convert::to_short(std::vector<uint8_t>::iterator index) {
    uint8_t bytes[] = {*(index),*(index+1)};
    int16_t  result = bytes[1] << 8 | bytes[0];
    return result;
}

float convert::to_float(std::vector<uint8_t>::iterator index){
    uint8_t bytes[] = {*index,*(index+1) ,*(index+2),*(index+3)};
    float result = 0;
    result = bytes[3]<<24 | bytes[2]<<16|bytes[1] << 8 | bytes[0];
    return result;
}

int32_t convert::to_long(std::vector<uint8_t>::iterator index) {
    uint8_t bytes[] = {*index,*(index+1),*(index+2),*(index+3)};
    int32_t result = bytes[3] << 24 | bytes[2] << 16 | bytes[1] << 8 | bytes[0];
    return result;
}