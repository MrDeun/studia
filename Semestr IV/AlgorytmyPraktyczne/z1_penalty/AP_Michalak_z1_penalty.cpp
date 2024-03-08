#include <cmath>
#include <iostream>

struct FifaData {
    long long groups;
    long long teams_per_group;
    long long advancees;
    long long direct;
};

long long factorial(long long value)
{
    if(value == 0)
        return 0;
    if(value == 1)
        return 1;
    return value * factorial(value - 1);
}

void collectData(FifaData& data)
{
    std::cin >> data.groups;
    std::cin >> data.teams_per_group;
    std::cin >> data.advancees;
    std::cin >> data.direct;
    return;
}

bool is_power_of_two(long long value)
{
    if (value == 0)
        return false;
    return ceil(log2(value)) == floor(log2(value));
}

long long new_teams(const FifaData& data)
{
    long long teams_from_data = (data.advancees * data.groups) + data.direct;
    long long new_teams = 0;
    while (!is_power_of_two(teams_from_data + new_teams))
    {
        new_teams++;
    }

    return new_teams;
}

long long matches_from_finals(long long teams_in_finals)
{
    long long result = 0;
    while (teams_in_finals != 2)
    {
        teams_in_finals = teams_in_finals/2;
        result += teams_in_finals;
    }
    return ++result;
}

long long total_matches(const FifaData& data, const long long new_teams)
{
    long long matches_from_quali = data.groups * factorial(data.teams_per_group - 1);
    long long teams_in_finals = (data.groups * data.advancees) + new_teams + data.direct;
    long long _matches_from_finals = matches_from_finals(teams_in_finals);
    return _matches_from_finals + matches_from_quali;
}

int main()
{
    FifaData data;
    while (true)
    {
        collectData(data);
        if (
            data.groups == -1 &&
            data.teams_per_group == -1 &&
            data.advancees == -1 &&
            data.direct == -1 
        )   return 0;

        long long _new_teams = new_teams(data);
        long long _total_matches = total_matches(data, _new_teams);
        
        std::cout << data.groups 
                  << '*' << data.advancees
                  << '/' << data.teams_per_group
                  << '+' << data.direct
                  << '=' << _total_matches
                  << '+' << _new_teams << std::endl;
    }
       
}