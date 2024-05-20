//
// Created by Patryk on 19-May-24.
//

#ifndef DUNGEONCRAWLERCMAKE_READ_FILE_H
#define DUNGEONCRAWLERCMAKE_READ_FILE_H

#include <fstream>

namespace reader {
    size_t read_size(std::ifstream& file){
        char buf[8];
        file.read(buf,8);
        size_t result = buf[7] << 56 |
                        buf[6] << 48 |
                        buf[5] << 40 |
                        buf[4] << 32 |
                        buf[3] << 24 |
                        buf[2] << 16 |
                        buf[1] << 8 |
                        buf[0];
        return result;
    }
};


#endif //DUNGEONCRAWLERCMAKE_READ_FILE_H
