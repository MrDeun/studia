#include <iostream>
#include "utils.h"

int main()
{
    double cel_temp = 17.0;

    std::cout << "\n In European Measurment: "<< cel_temp;
    std::cout << "\n In Scientific Measurment: "<< temp_util::cel_to_kel(cel_temp) ;
    std::cout << "\n In American Measurment: "<< temp_util::cel_to_fahr(cel_temp) ;

    return 0;
}