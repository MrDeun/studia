#include <iostream>
#include <cstdint>
#include <string>
#include <algorithm>
uint64_t reverse_it(uint64_t input){
    std::string str_input = std::to_string(input);
    std::reverse(str_input.begin(),str_input.end());
    return std::stoull(str_input);
}

int main() {
    size_t cases;
    std::cin >> cases;
    for(size_t i{};i<cases;i++) {
        uint64_t first{}, second{};
        std::cin >> first >> second;
        first = reverse_it(first);
        second = reverse_it(second);
        std::cout << reverse_it(first+second) <<"\n";
    }
}