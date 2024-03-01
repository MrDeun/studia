#include <iostream>
union Data{
    short int two_byte;
    char swap_area[2];
};

void swap(Data& this_data)
{
    char temp = this_data.swap_area[1];
    this_data.swap_area[1] = this_data.swap_area[0];
    this_data.swap_area[0] = temp;

    return; 
}

int main(){
    union Data this_data;

    this_data.two_byte = 1;

    std::cout << "Before byte swap: " << this_data.two_byte << std::endl;
    swap(this_data);
    std::cout << "After byte swap: " << this_data.two_byte << std::endl;

    return 0;
}
