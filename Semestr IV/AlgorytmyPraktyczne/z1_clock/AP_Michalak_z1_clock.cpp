// TEMPLATE OF A CODE FILE
#include <iomanip>
#include <iostream>
#include <cmath>

#define HR12_MILISEC 4320000

struct Clock{
    long hour; // 0 <= H < 12;
    long minutes; // 0 <= M < 60
    long seconds; // 0 <= M < 60
    long miliseconds; // 0 <= M < 100
    long long totalTimes_miliSec;
}; 

void collectData(Clock& clockOne,Clock& clockTwo,float& radius)
{
    std::cin >> clockOne.hour >> clockOne.minutes >> clockOne.seconds >> clockOne.miliseconds;
    std::cin >> clockTwo.hour >> clockTwo.minutes >> clockTwo.seconds >> clockTwo.miliseconds;
    std::cin >> radius;
    
    clockOne.totalTimes_miliSec = (clockOne.hour * 360000) + (clockOne.minutes * 6000) + (clockOne.seconds * 100) + clockOne.miliseconds; 
    clockTwo.totalTimes_miliSec = (clockTwo.hour * 360000) + (clockTwo.minutes * 6000) + (clockTwo.seconds * 100) + clockTwo.miliseconds; 
    return;
}

int main()
{

    Clock clockOne, clockTwo;
    float radius{};
    size_t count{};

    std::cin >> count;

    for (size_t i = 0; i < count; i++)
    {
        collectData(clockOne, clockTwo, radius);
        double time_diff = double(clockTwo.totalTimes_miliSec - clockOne.totalTimes_miliSec) / HR12_MILISEC;
        double angel_diff = time_diff * 2 * M_PI;
        std::cout << std::fixed << std::setprecision(3) << i+1 << ". " << radius * radius * angel_diff / 2 << "\n";
    }

    return 0;
}

