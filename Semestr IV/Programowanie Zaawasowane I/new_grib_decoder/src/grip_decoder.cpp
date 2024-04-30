//
// Created by Patryk on 24-Apr-24.
//

#include "grip_decoder.h"

grip_decoder::grip_decoder(const char* filename) {
        std::ifstream file_stream(filename, std::ios::binary);
        file_stream.unsetf(std::ios::skipws);

        std::streampos file_size;
        file_stream.seekg(0, std::ios::end);
        file_size = file_stream.tellg();
        file_stream.seekg(0, std::ios::beg);

        byte_vector vec;
        vec.reserve(file_size);
        vec.insert(vec.begin(), std::istream_iterator<char>(file_stream),
                   std::istream_iterator<char>());

        byte_array = vec;
        cursor = byte_array.begin();
}

bool grip_decoder::find_grip() {
    byte_vector vec_grip = {'G','R','I','P'};
    cursor = std::search(cursor,byte_array.end(),vec_grip.begin(),vec_grip.end());
    if (cursor == byte_array.end()) {
        return false;
    } else {
        grip_size = convert::to_size(cursor+4);
        std::cout << "Size of GRIP message: " << grip_size << '\n';
        cursor += 8; // First byte of PDS
        return true;
    }
}

void grip_decoder::signal_flags(const uint8_t& data) {
    switch (data) {
        case 0b11000000:
            GDS_exists = true;
            BMS_exists = true;
            break;
        case 0b10000000:
            GDS_exists = true;
            BMS_exists = false;
            break;
        case 0b01000000:
            GDS_exists = false;
            BMS_exists = true;
            break;
        default:
            GDS_exists = false;
            BMS_exists = false;
            break;
    }
    return;
}

void print_data(byte_vector::iterator year_byte){
    uint8_t year = *(year_byte);
    uint8_t month = *(year_byte+1);
    uint8_t day = *(year_byte+2);
    uint8_t hour = *(year_byte+3);
    uint8_t minute = *(year_byte+4);
    std::cout << "DATE: "
              << day << "-"
              <<month<< "-"
              <<year;
    std::cout <<' '<< hour << ":" << minute << '\n';
    return;
}

void grip_decoder::scan_PDS() {
    PDS_size = convert::to_size(cursor);
    std::cout << "Size of PDS message: " << PDS_size << '\n';
    cursor += 7; // Flag byte
    signal_flags(*cursor);
    cursor += 5; // Year byte
    print_date(cursor);
    cursor += PDS_size - 12; // first byte of gds/bms/bds
    return;
}

void grip_decoder::read_GDS(){
    std::cout << "Size of GDS message: " <<convert::to_size(cursor) << '\n';
    cursor += 6;
    std::cout << "Count of points along latitude circle: "<<convert::to_short(cursor) <<'\n';
    cursor += 2;
    std::cout << "Count of points along longitude meridean: "<<convert::to_short(cursor) <<'\n';
    cursor += 2;
    std::cout << "Latitude 1: " << (float)convert::to_size(cursor)*1000;
    cursor += 3;
    std::cout << "Longitude 1: " << (float)convert::to_size(cursor)*1000;
    cursor += 4;
    std::cout << "Latitude 1: " << (float)convert::to_size(cursor)*1000;
    cursor += 3;
    std::cout << "Longitude 1: " << (float)convert::to_size(cursor)*1000;
}
//void grip_decoder::read_BDS(){}
//void grip_decoder::read_BMS(){}

void grip_decoder::scan_rest() {
    // Cursor now is in first byte of GDS/BMS/BDS
    if (GDS_exists){
        read_GDS();
    }
    if (BMS_exists){
        //read_BMS();
    }
    //read_BDS();
}