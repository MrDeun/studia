#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>

void create_vector(std::vector<int>& vector_in, size_t new_size)
{
    vector_in.clear();
    for(size_t i = 0; i < new_size; i++)
    {
        int new_value;
        std::cin >> new_value;
        vector_in.push_back(new_value);
    }
    return;
}

int calculate_best(const std::vector<int>& helix_1, const std::vector<int>& helix_2,std::vector<int> common_elements)
{
    if (common_elements.empty())
    {
        int sum_1 = std::accumulate(helix_1.begin(),helix_1.end(),0);
        int sum_2 = std::accumulate(helix_2.begin(),helix_2.end(),0);

        if (sum_1 > sum_2)
            return sum_1;
        else
            return sum_2;
        
    }
    

    int res{};
    auto checkpoint_1 = helix_1.begin();
    auto checkpoint_2 = helix_2.begin();
    
    auto next_checkpoint_1 = helix_1.begin();
    auto next_checkpoint_2 = helix_2.begin();
    do
    {
        next_checkpoint_1 = std::find(checkpoint_1,helix_1.end(),common_elements.back());
        next_checkpoint_2 = std::find(checkpoint_2,helix_2.end(),common_elements.back());

        int sum_1 = std::accumulate(checkpoint_1,next_checkpoint_1,0);
        int sum_2 = std::accumulate(checkpoint_2,next_checkpoint_2,0);

        if (sum_1 > sum_2) res += sum_1;
        else res += sum_2;

        checkpoint_1 = next_checkpoint_1;
        checkpoint_2 = next_checkpoint_2;
        common_elements.pop_back();
    }while (next_checkpoint_1 != helix_1.end() && next_checkpoint_2 != helix_2.end() && !common_elements.empty());
    return res;
}

int main()
{
    size_t helix_size;
    std::vector<int> helix_1;
    std::vector<int> helix_2;
    while (true)
    {
        std::cin >> helix_size;
        if (helix_size == 0) 
            return 0;
        create_vector(helix_1,helix_size);
        std::cin >> helix_size;
        create_vector(helix_2,helix_size);

        std::vector<int> common_elements;
        std::set_intersection(
        helix_1.begin(),helix_1.end(),
        helix_2.begin(),helix_2.end(),
        std::back_inserter(common_elements)
        );
        
        std::reverse(common_elements.begin(),common_elements.end());
        std::cout << calculate_best(helix_1,helix_2,common_elements) << std::endl;
        common_elements.clear();
    }
    return 0;
}