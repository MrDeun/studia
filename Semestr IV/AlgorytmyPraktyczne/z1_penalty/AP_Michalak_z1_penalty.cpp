#include <iostream>
#include <cstdint>
struct InputData{
    int64_t groups;
    int64_t teams_per_group;
    int64_t advancees;
    int64_t direct;
};

InputData collectData(){
    InputData new_data;
    std::cin >> new_data.groups 
             >> new_data.teams_per_group 
             >> new_data.advancees 
             >> new_data.direct;
    return new_data;
}

int64_t two_check(int64_t testee){
    while(testee%2 == 0){
        testee = testee / 2;
    }
    return testee;
}

int64_t checkKnockout(int64_t knockout_teams){
    int64_t check = two_check(knockout_teams);
    if(check != 1){
        int64_t temp = 1;
        while(temp < knockout_teams){
            temp = temp*2;
        }
        return temp;
    }
    return knockout_teams;
}

    
int64_t newTeams(int64_t finals_check, int64_t knockout_teams){
    if (finals_check == 0){
        return 0;
    } else {
        int64_t new_teams = finals_check - knockout_teams;
        return new_teams;
    }
}

int64_t finalMatches(int64_t knockout_check){
    int64_t matches_count = 0;
    while(knockout_check>1){
        matches_count += knockout_check/2;
        knockout_check = knockout_check/2;
    }
    return matches_count;
}

void print_result(InputData data, int64_t new_teams, int64_t total_matches){
    std::cout << data.groups
              << '*' <<data.advancees
              << '/' <<data.teams_per_group
              << '+' <<data.direct
              << '=' <<total_matches
              << '+' <<new_teams << std::endl;
}

int main(){
    while (true){
        InputData data = collectData();
        if (data.groups == -1 && 
            data.teams_per_group == -1 && 
            data.advancees == -1 && 
            data.direct == -1) return 0;
        
        int64_t matches_in_group = (data.teams_per_group * ((data.teams_per_group -1)))/2;
        int64_t matches_in_quali = matches_in_group * data.groups;
        int64_t knockout_teams = data.groups * data.advancees + data.direct;
        
        int64_t finals_check = checkKnockout(knockout_teams);
        int64_t new_teams = newTeams(finals_check,knockout_teams);
        int64_t matches_in_finals = finalMatches(finals_check);

        print_result(data,new_teams,matches_in_finals+matches_in_quali);
    }
    
}