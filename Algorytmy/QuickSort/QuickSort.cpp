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

void Swap(int *Array, int First, int Second)
{
    int Temp=Array[First];
    Array[First]=Array[Second];
    Array[Second]=Temp;
    return;
}

void QuickSort(int *Array, int Left, int Right)
{
    int Pivot{},i{};
    if (Left<Right)
    {
        Pivot=Left;
        int i=Left+1;
    }

    else
        return;

    while (true)
    {

    
    if(i>Right)
        {
            Swap(Array,Pivot,Left);
            QuickSort(Array,Left,Pivot-1);
            QuickSort(Array,Pivot+1,Right);
            return;
        }

    else
        {
            if (Array[i]<Array[Left])
            {
                Pivot++;
                Swap(Array,Pivot,i);
            }
            i++;
        }
    }
    
}

int main()
{

    int *Array=RandomArray(20);
    ShowArray(Array,20);
    QuickSort(Array,0,20);
    ShowArray(Array,20);

    return 0;
}