//
// Created by mrdeun on 08.06.24.
//

#include <iostream>
#include <fstream>
int main(){
    size_t size_x,size_y;
    std::cin >> size_x >> size_y;

    std::string source_file{};
    std::cin >> source_file;

    std::ifstream file(source_file);
    std::ofstream bin_file("map.txt",std::ios::binary);
    bin_file.unsetf(std::ios::skipws);
}