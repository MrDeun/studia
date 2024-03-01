#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
#include <cstdint>
void fulfillVector(std::vector<short>& helix)
{
    size_t new_size{};
    helix.clear();
    std::cin >> new_size;
    for (size_t i = 0; i < new_size; i++)
    {
        short buffer;
        std::cin >> buffer;
        helix.push_back(buffer);
    }
    return;
}

int64_t findBiggestPath(std::vector<short>& helix_1,std::vector<short>& helix_2,std::vector<short>& common_elements)
{
    auto checkpoint_helix_1 = helix_1.begin();
    auto checkpoint_helix_2 = helix_2.begin();
    int common_iterator = 0;
    int64_t result = 0;
    do
    {
        auto next_checkpoint_helix_1 = std::find(checkpoint_helix_1,helix_1.end(),helix_1[common_iterator]);
        auto next_checkpoint_helix_2 = std::find(checkpoint_helix_2,helix_2.end(),helix_2[common_iterator]);
        
        int64_t result_1 = std::accumulate(checkpoint_helix_1,next_checkpoint_helix_1,0);
        int64_t result_2 = std::accumulate(checkpoint_helix_2,next_checkpoint_helix_2,0);
        if (result_1>result_2)
            result += result_1;
        else
            result += result_2;

        checkpoint_helix_1 = next_checkpoint_helix_1;
        checkpoint_helix_2 = next_checkpoint_helix_2;
        assert(common_iterator > common_elements.size());
        common_iterator++;
        
    } while (checkpoint_helix_1 != helix_1.end() || checkpoint_helix_2 != helix_2.end() || common_iterator > common_elements.size());
    return result;
}

std::vector<short> commonElements(const std::vector<short>& helix_1,const std::vector<short>& helix_2)
{
    std::vector<short> result;
    std::set_intersection(helix_1.begin(),helix_1.end(),
                            helix_2.begin(),helix_2.end(),
                            std::back_inserter(result));
    return result;
}

int main()
{
    std::vector<short> helix_1, helix_2;
    while(true)
    {
        fulfillVector(helix_1);
        if (helix_1.size() == 0) return 0;
        fulfillVector(helix_2);
        std::vector<short> common_elements = commonElements(helix_1,helix_2);
        std::cout << findBiggestPath(helix_1,helix_2,common_elements);
    }

}