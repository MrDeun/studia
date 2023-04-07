#include<iostream>
#include<fstream>

int *RandomArray(int ArrayLength)
{
    int *Array = new int[ArrayLength];
    for (int i = 0; i < ArrayLength; i++)
    {
        Array[i]=rand()%1000;
    }
    return Array;
}

void ShowArray(int *Array, int ArrayLength)
{
    for(int i=0;i<ArrayLength;i++)
    {
        std::cout<<Array[i]<<" ";
        if(i%10==9)
            std::cout<<std::endl;
    }
    std::cout<<"\n\n\n";
    return;
}

double QuickSort(int *Array, int Begin, int End)
{
    int Position=0;
    if (Array[Begin]<Array[End])
    {
        Position=Array[Left];
    }
    
}

int main()
{



    return 0;
}