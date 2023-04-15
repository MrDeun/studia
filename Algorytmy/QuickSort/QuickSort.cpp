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

double QuickSort(int* Array, int Left, int Right)
 {

    int pos{};
    double Result{0};
    if (Left < Right) 
    {
        pos = Left;
        for (int i = Left + 1; i <= Right; i++) 
        {
            if (Array[i] < Array[Left]) 
            {
                pos++;
                Swap(Array, pos, i);
            }
            Result++;
  
        }
        Swap(Array, pos, Left);
        QuickSort(Array, Left, pos - 1);
        QuickSort(Array, pos + 1, Right);

    }

    return Result;

}
  


int main()
{
    int *Array=RandomArray(20);
    ShowArray(Array,20);
    std::cout<<std::endl<<"Ilosc porownan: "<<QuickSort(Array,0,20)<<std::endl;
    ShowArray(Array,20);

    return 0;
}