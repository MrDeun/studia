// TEMPLATE OF A CODE FILE
#include <iostream>

#define HR12_MILISEC 4320000
#define PI 3.1415

struct Clock{
    long hour; // 0 <= H < 12;
    long minutes; // 0 <= M < 60
    long seconds; // 0 <= M < 60
    long miliseconds; // 0 <= M < 100
    long long totalTimes_miliSec;
}; 

void fillClock(long* clock_buffer, Clock& clock)
{
    clock.hour = clock_buffer[0];
    clock.minutes = clock_buffer[1];
    clock.seconds = clock_buffer[2];
    clock.miliseconds = clock_buffer[3];

    clock.totalTimes_miliSec = clock.hour * 60 * 60 * 100;
    clock.totalTimes_miliSec += clock.minutes * 60 * 100;
    clock.totalTimes_miliSec += clock.seconds * 100;
    clock.totalTimes_miliSec += clock.miliseconds;

    return;
}

void collectData(Clock& clockOne,Clock& clockTwo,float& radius)
{
    long clock_buffer[4];
    
    for(long i=0;i< 4;i++)
    {
        std::cin >> clock_buffer[i];
    }

    fillClock(clock_buffer,clockOne);

    for(long i=0;i< 4;i++)
    {
        std::cin >> clock_buffer[i];
    }

    fillClock(clock_buffer,clockTwo);

    std::cin >> radius;
    
    return;
}

int main()
{

    Clock clockOne, clockTwo;
    float radius{};
    long count{};

    std::cin >> count;

    for (size_t i = 0; i < count; i++)
    {
        collectData(clockOne, clockTwo, radius);
        double time_diff = double(clockTwo.totalTimes_miliSec - clockOne.totalTimes_miliSec) / HR12_MILISEC;
        double angel_diff = time_diff * 2 * 3.1415;
        std::cout << i+1 << ". " << radius * radius * angel_diff / 2 << "\n";
    }

    return 0;
}

