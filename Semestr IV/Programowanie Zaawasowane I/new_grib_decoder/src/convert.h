//
// Created by Patryk on 24-Apr-24.
//

#ifndef NEW_GRIB_DECODER_CONVERT_H
#define NEW_GRIB_DECODER_CONVERT_H


#include <cstdint>
#include <vector>



namespace convert {
    uint32_t to_size(std::vector<uint8_t>::iterator index);
    uint8_t to_byte(std::vector<uint8_t>::iterator index) {return *index;}
    int32_t to_long(std::vector<uint8_t>::iterator index);
    float to_float(std::vector<uint8_t>::iterator index);
};


#endif //NEW_GRIB_DECODER_CONVERT_H
