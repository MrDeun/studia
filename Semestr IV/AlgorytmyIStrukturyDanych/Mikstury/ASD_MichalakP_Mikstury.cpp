#include <iostream>
#include <vector>
class potion_node {
    public:
        size_t index;
        int price;
        potion_node(size_t index_in, int price_in):index(index_in),price(price_in){}
        ~potion_node(){}
};

// void collect_test_case(std::vector<potion_node>& all_potions,){
//     if (!all_potions.empty()){
//         all_potions.clear();
//     }
    
// }


int main() {
    size_t test_cases;
    std::cin >> test_cases;
    for (size_t i = 0; i < test_cases; i++){
        size_t mixture_amount,transmutation_routes;
        std::vector<potion_node> all_potions;
        std::cin >> mixture_amount >> transmutation_routes;
        for (size_t i = 0; i < mixture_amount; i++){
            int price;
            std::cin >> price;
            all_potions.push_back(potion_node(i,price));
        }
        
        

    }
    
}