#include "grib_decoder.h"
#include <iostream>
#include <conio.h>
int main(int argc, char** argv) {
//    if (argc < 2){
//        std::cout << "No filename argument!\n";
//        return -1;
//    }
    const char* filename = "msg.bin";
    grib_decoder GRIBDecoder(filename);
    if(GRIBDecoder.find_GRIB()){
        GRIBDecoder.scan_PDS();
        if(getch() == 'q'){
            return 0;
        }
        GRIBDecoder.scan_rest();
    }
    std::cout << "Reached EOF" << std::endl;
    return 0;
}
