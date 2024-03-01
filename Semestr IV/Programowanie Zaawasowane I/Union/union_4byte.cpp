#include <iostream>

union FourByte{
    long four_byte;
    char swap_area[4];
};

void swap(FourByte& this_data)
{
    for (size_t i = 0; i < 2; i++)
    {
        char temp = this_data.swap_area[i];
        this_data.swap_area[i] = this_data.swap_area[3 - i];
        this_data.swap_area[3 - i] = temp;
    }
    
    return;
}

int main()
{
    union FourByte data;
    data.four_byte = 255;
    std::cout << "Before swap: " << data.four_byte << std::endl;
    swap(data);
    std::cout << "After swap: " << data.four_byte << std::endl;
    return 0;
}
