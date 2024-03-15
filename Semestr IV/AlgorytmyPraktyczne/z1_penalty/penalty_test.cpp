#include <cstdint>
#include <iostream>
#include <cstdint>
#include <cmath>
struct FifaData {
    int64_t groups;
    int64_t teams_per_group;
    int64_t advancees;
    int64_t direct;
};

FifaData collectData() {
    FifaData new_data;
    new_data.groups = 65536;
    new_data.teams_per_group = 65536;
    new_data.advancees = 65536;
    new_data.direct = 256;
    return new_data;
}

bool is_power_of_two(int64_t amount) {
    return std::log2l(static_cast<long double>(amount)) == 
        floor(std::log2l(static_cast<long double>(amount)));
}

int64_t new_teams(FifaData data) {
    int64_t current_teams = (data.groups * data.advancees) + data.direct;
    int64_t new_teams = 0;
    while(!is_power_of_two(current_teams + new_teams)) {
        ++new_teams;
    }
    return new_teams;
}

int64_t matches_in_knockout(int64_t teams) {
    if (teams <= 2) {
        return 1;
    }
    return matches_in_knockout(teams/2) + teams/2;
}

int64_t total_matches(FifaData data, int64_t new_teams) {
    int64_t matches_in_quali = data.groups * ((data.teams_per_group * (data.teams_per_group-1))/2);
    int64_t _matches_in_knockout = 
        matches_in_knockout(new_teams + (data.groups * data.advancees) + data.direct);
    return matches_in_quali + _matches_in_knockout; 
}

void output_values(const FifaData& data, const int64_t& _new_teams, const int64_t& _total_matches) {
    std::cout << data.groups
              << '*' <<data.advancees
              << '/' <<data.teams_per_group
              << '+' <<data.direct
              << '=' <<_total_matches
              << '+' <<_new_teams << std::endl;

}

int main() {
    FifaData data = collectData();

    int64_t _new_teams = new_teams(data);
    int64_t _total_matches = total_matches(data,_new_teams);

    output_values(data,_new_teams,_total_matches);
}
