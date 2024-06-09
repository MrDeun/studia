//
// Created by Patryk on 24-Apr-24.
//

#ifndef NEW_GRIB_DECODER_GRIB_DECODER_H
#define NEW_GRIB_DECODER_GRIB_DECODER_H


#include <cstdint>
#include <vector>
#include <iterator>

using byte_vector = std::vector<uint8_t>;

class grib_decoder {
    private:
        byte_vector byte_array;
        byte_vector::iterator cursor;
        uint32_t grib_size,PDS_size,GDS_size,BMS_size;
        bool GDS_exists, BMS_exists;
        void signal_flags(const uint8_t& data);
        void print_date(byte_vector::iterator year_byte);
    public:
        void read_GDS();
        void scan_PDS();
        void read_BMS();
        void read_BDS();
        grib_decoder(const char* filename);
        ~grib_decoder() = default;
        bool find_GRIB();
        void scan_rest();
};


#endif //NEW_GRIB_DECODER_GRIB_DECODER_H
