#include <cstdint>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
std::vector<int16_t> create_helix(size_t helix_size){
    std::vector<int16_t> new_helix;
    for (size_t i = 0; i < helix_size; i++){
        int16_t temp;
        std::cin >> temp;
        new_helix.push_back(temp); 
    }
    return new_helix;
}

std::vector<std::pair<size_t,size_t>> check_intersection(const std::vector<int16_t>& helix_1,const std::vector<int16_t>& helix_2){
    std::vector<std::pair<size_t,size_t>> intersections;
    for (size_t i = 0; i < helix_1.size(); i++){
        for (size_t j = 0; j < helix_2.size(); j++){
            if (helix_1[i] == helix_2[j]){
                intersections.push_back(std::make_pair(i, j));
            } 
        }
    }
    return intersections;
}

int64_t find_max(
    std::vector<int16_t> helix_1,
    std::vector<int16_t> helix_2,
    std::vector<std::pair<size_t,size_t>> intersections
) {
    int64_t result = 0;

    if(intersections.empty()){
        int64_t sum_1 = std::accumulate(helix_1.begin(),helix_1.end(),0);
        int64_t sum_2 = std::accumulate(helix_2.begin(),helix_2.end(),0);
        return sum_1 > sum_2 ? sum_1 : sum_2;
    }

    size_t iterator_1{}, iterator_2{};
    for (auto intersection : intersections){
        int64_t sum_1{}, sum_2{};
        for (; iterator_1 < intersection.first; iterator_1++){
            sum_1 += helix_1[iterator_1];
        }
        for (; iterator_2 < intersection.second; iterator_2++){
            sum_2 += helix_2[iterator_2];
        }
        
    }
    
    
}

int main(){
    size_t helix_size{};
    std::cin >> helix_size;
    while (helix_size != 0){
        auto helix_1 = create_helix(helix_size);
        std::cin >> helix_size;
        auto helix_2 = create_helix(helix_size);
        auto intersection_points = check_intersection(helix_1,helix_2);

        std::cout << find_max(helix_1,helix_2,intersection_points);

        helix_1.clear();
        helix_2.clear();
        std::cin >> helix_size;
    }
    return 0;
}