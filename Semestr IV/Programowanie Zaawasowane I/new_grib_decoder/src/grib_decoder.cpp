//
// Created by Patryk on 24-Apr-24.
//

#include "grib_decoder.h"
#include "convert.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <cstdint>

std::ostream &operator<<(std::ostream &output, byte_vector vec_in) {
  output << '{';
  for (auto &byte : vec_in) {
    output << ' ' << byte << ',';
  }
  output << "}";
  return output;
}

grib_decoder::grib_decoder(const char *filename) {
  std::cout << "Trying to read grib file...\n";
  std::ifstream file_stream(filename, std::ios::binary);
  file_stream.unsetf(std::ios::skipws);

  std::streampos file_size;
  file_stream.seekg(0, std::ios::end);
  file_size = file_stream.tellg();
  file_stream.seekg(0, std::ios::beg);

  byte_vector vec(file_size);
  std::cout << "Vector Size: " << vec.size() << '\n';
  vec.insert(vec.begin(), std::istream_iterator<char>(file_stream),
             std::istream_iterator<char>());
  byte_array = vec;
  cursor = byte_array.begin();
  std::cout << "Finished reading header of grib\n";
  std::cout << "\n===============================\n";
}

bool grib_decoder::find_GRIB() {
  std::cout << "Finding grib keyword...\n";
  // std::cout << byte_array;
  byte_vector vec_grib = {'G', 'R', 'I', 'B'};
  cursor =
      std::search(cursor, byte_array.end(), vec_grib.begin(), vec_grib.end());
  if (cursor == byte_array.end()) {
    std::cout << "grib NOT FOUND!\n";
    return false;
  } else {
    grib_size = convert::to_size(cursor + 4);
    std::cout << "Size of grib message: " << grib_size << '\n';
    cursor += 8; // First byte of PDS
    return true;
  }
}

void grib_decoder::signal_flags(const uint8_t &data) {
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

void grib_decoder::print_date(byte_vector::iterator year_byte) {
  uint16_t year = convert::to_byte(year_byte);
  uint16_t month = convert::to_byte(year_byte + 1);
  uint16_t day = convert::to_byte(year_byte + 2);
  uint16_t hour = convert::to_byte(year_byte + 3);
  uint16_t minute = convert::to_byte(year_byte + 4);
  std::cout << "DATE: " << day << "-" << month << "-" << year << '\n';
  std::cout << "TIME: ";
  std::cout << (hour > 9 ? "" : "0") << hour << ":";
  std::cout << (minute > 9 ? "" : "0") << minute << "\n";
  return;
}

void grib_decoder::scan_PDS() {
  std::cout << "Scanning PDS...\n";
  PDS_size = convert::to_size(cursor);
  std::cout << "Size of PDS message: " << PDS_size << '\n';
  cursor += 7; // Flag byte
  signal_flags(*cursor);
  cursor += 5; // Year byte
  print_date(cursor);
  cursor += PDS_size - 12; // first byte of gds/bms/bds
  std::cout << "Finished reading PDS...\n===============================\n";
  return;
}

void grib_decoder::read_GDS() {
  uint32_t msg_size = convert::to_size(cursor);
  std::cout << "Size of GDS message: " << msg_size << '\n';
  cursor += 6;
  std::cout << "Count of points along latitude circle: "
            << convert::to_short(cursor) << '\n';
  cursor += 2;
  std::cout << "Count of points along longitude meridean: "
            << convert::to_short(cursor) << std::endl;
  cursor += 2;
  std::cout << "Latitude 1: " << convert::to_size(cursor)  << '\n';
  cursor += 3;
  std::cout << "Longitude 1: " << convert::to_float3(cursor)
            << '\n';
  cursor += 4;
  std::cout << "Latitude 2: " << convert::to_float3(cursor)  << '\n';
  cursor += 3;
  std::cout << "Longitude 2: " << convert::to_float3(cursor)
            << '\n';
  std::cout << "\n===============================\n";
  cursor += msg_size - 20;
}
void grib_decoder::read_BDS() {
  uint32_t msg_size = convert::to_size(cursor);
  std::cout << "Size of BDS Message: " << msg_size << '\n';
}
void grib_decoder::read_BMS() {
  std::cout << "BMS IS NOT SUPPORTED YET!\n";
  assert(false);
}

void grib_decoder::scan_rest() {
  // Cursor now is in first byte of GDS/BMS/BDS
  if (GDS_exists) {
    read_GDS();
  }
  if (BMS_exists) {
    read_BMS();
  }
  read_BDS();
}