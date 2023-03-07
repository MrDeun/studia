#include<iostream>
#include<time.h>
#include<ctime>
#include<Windows.h>

using namespace std;

void SleepClear(int Time)
{
    Sleep(Time);
    system("CLS");
}

void Spin(int Time)
{
    SleepClear(Time);
    for(int i=0;i<30;i++)
    {
        cout<<"|";
        SleepClear(Time);
        cout<<"/";
        SleepClear(Time);
        cout<<"-";
        SleepClear(Time);
        cout<<"\\";
        SleepClear(Time);

    }
}

int main()
{
    int time;
    cin>>time;
    Spin(time);
    return 0;
}