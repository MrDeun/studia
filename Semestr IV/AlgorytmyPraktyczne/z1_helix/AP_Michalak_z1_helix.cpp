#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>


int calculate_best(const std::vector<short>& helix_1, const std::vector<short>& helix_2, const std::vector<short>& common_elements)
{

}

int main()
{
    std::vector<short> helix_1{3, 5, 7, 9, 20, 25, 30, 40, 55, 56, 57, 60, 62};
    std::vector<short> helix_2{1, 4, 7, 11, 14, 25, 44, 47, 55, 57, 100};

    std::vector<short> common_elements;
    std::set_intersection(
        helix_1.begin(),helix_1.end(),
        helix_2.begin(),helix_2.end(),
        std::back_inserter(common_elements)
    );

    std::reverse(common_elements.begin(),common_elements.end());
    std::cout << calculate_best(helix_1,helix_2,common_elements);
    


    return 0;
}