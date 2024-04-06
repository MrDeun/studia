#include <iostream>
#include <cstdint>

const uint16_t required_steps = 3000;

uint16_t minutes_required(uint16_t steps_per_minute) {
    uint16_t foot_count = 0;
    for (size_t minutes_passed = 0; minutes_passed < 15; minutes_passed++){
        foot_count += steps_per_minute;
        if (foot_count >= 3000){
            return minutes_passed+1;
        }
    }
    return 15;
}

int main(){
    size_t test_cases;
    std::cin >> test_cases;
    for (size_t i = 0; i < test_cases; i++) {
        uint16_t steps_per_minute;
        std::cin >> steps_per_minute;
        std::cout << minutes_required(steps_per_minute) << std::endl;
    }
    return 0;
}