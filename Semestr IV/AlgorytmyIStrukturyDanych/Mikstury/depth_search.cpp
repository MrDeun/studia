#include <cstddef>
#include <vector>
#include <iostream>
#include <algorithm>
struct mixture{
    size_t index;
    int value;
    mixture(size_t id_in, int value_in):index(value_in),value(value_in){}
};
struct {bool operator()(mixture a,mixture b){return a.value<b.value;}} mix_compare;

using map_edges = std::vector<std::vector<size_t>>;




int main(){
    size_t test_cases{};
    std::cin >> test_cases;
    for (size_t i = 0; test_cases>i; i++) {
        size_t mix_size, trans_size;
        
    }
}