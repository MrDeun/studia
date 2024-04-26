//
// Created by Patryk on 24-Apr-24.
//

#ifndef NEW_GRIB_DECODER_GRIP_DECODER_H
#define NEW_GRIB_DECODER_GRIP_DECODER_H

#include "convert.h"

#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>

using byte_vector = std::vector<uint8_t>;

class grip_decoder {
    private:
        byte_vector byte_array;
        byte_vector::iterator cursor;
        uint32_t grip_size,PDS_size,GDS_size,BMS_size;
        bool GDS_exists, BMS_exists;
        void signal_flags(const uint8_t& data);
        void print_date(byte_vector::iterator year_byte);
    public:
        grip_decoder(const char* filename);
        ~grip_decoder() = default;
        bool find_grip();
        void scan_PDS();
};


#endif //NEW_GRIB_DECODER_GRIP_DECODER_H
