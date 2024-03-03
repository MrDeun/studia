#include <cassert>
#include <iostream>
#include <cstdint>
struct Data {
    int32_t groups;
    int32_t teams_per_group;
    int32_t advancees;
    int32_t direct;
};

bool is_power_of_two(long long x) {
    return !(x == 0) && !(x & (x - 1));
}

int mylog2 (unsigned int val) {
    if (val == 0) return UINT_MAX;
    if (val == 1) return 0;
    unsigned int ret = 0;
    while (val > 1) {
        val >>= 1;
        ret++;
    }
    return ret;
}


void collectData(Data& our_data)
{
    std::cin >> our_data.groups >> our_data.teams_per_group >> our_data.advancees >> our_data.direct;
    return;
}


long long new_teams(const Data& our_data)
{
    long long _new_teams = 0;
    while (!is_power_of_two((our_data.groups * our_data.advancees) + our_data.direct + _new_teams)) {
        _new_teams++;
    }

    return _new_teams;
}
long long matches_in_knockout(long long power_of_two)
{
    if(power_of_two == 2)
        {
            return 1;
        }
    else
        return mylog2(power_of_two) + matches_in_knockout(power_of_two/2);
}

long long total_matches(const Data& our_data, const long long& new_teams)
{
    assert(is_power_of_two((our_data.advancees * our_data.groups) + new_teams + our_data.direct));
    long long _matches_in_knockout = matches_in_knockout((our_data.advancees * our_data.groups) + new_teams + our_data.direct);
    return _matches_in_knockout;
}

int main()
{
    Data our_data;
    while(true)
    {
        collectData(our_data);
        if (
            our_data.groups == -1 &&
            our_data.teams_per_group == -1 &&
            our_data.advancees == -1 &&
            our_data.direct == -1
        )  return 0;

        long long _new_teams = new_teams(our_data);
        long long _total_matches = total_matches(our_data, _new_teams);

        std::cout << our_data.groups 
                  << "*" << our_data.advancees 
                  << "/" << our_data.teams_per_group 
                  << "+" << our_data.direct 
                  << "=" << _total_matches
                  << "+" << _new_teams;
    }
    
}