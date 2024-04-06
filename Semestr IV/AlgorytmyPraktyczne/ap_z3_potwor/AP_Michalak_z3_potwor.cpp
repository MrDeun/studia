#include <iostream>
#include <cstdint>
uint64_t factorialize(uint32_t pre_fact){
    if (pre_fact == 1){
        return 1;
    }
    return pre_fact*factorialize(pre_fact-1);
}

int main(){
    size_t test_cases;
    std::cin >> test_cases;
    for (size_t i = 0; i < test_cases; i++){
        uint32_t pre_fact;
        std::cin >> pre_fact;
        uint64_t factorial = factorialize(pre_fact);
    }
    
}