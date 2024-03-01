#include <iostream>

struct FIFA
{
    int group_count;
    int teams_per_group;
    int advance_to_knockout;
    int bypass_to_knockout;
};

bool should_exit(const FIFA& fifaInstance)
{
    return (fifaInstance.advance_to_knockout == -1 &&
            fifaInstance.bypass_to_knockout == -1 &&
            fifaInstance.teams_per_group == -1 &&
            fifaInstance.group_count == -1);
}
void CollectData(FIFA& fifaInstance)
{
    std::cin >> fifaInstance.group_count 
             >> fifaInstance.teams_per_group 
             >> fifaInstance.advance_to_knockout
             >> fifaInstance.bypass_to_knockout;
}

int main()
{
    FIFA fifaInstance;
    while(true)
    {
        CollectData(fifaInstance);
        if (should_exit(fifaInstance))
        {
            return 0;
        }
        
    }
    
}