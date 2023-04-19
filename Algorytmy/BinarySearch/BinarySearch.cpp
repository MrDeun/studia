#include<iostream>

int BinarySearch(int* Array,int ArrayLength,int Search)
{
    int Left=0,Right=ArrayLength-1,Mid{};
    while(Left<=Right)
    {
        Mid=(Left+Right)/2;
        if(Array[Mid]==Search)
            return Search;
        
        if(Array[Mid]<Search)
            Left=Mid+1;
        else
            Right=Mid+1;
            
    }
    return -1;
}

int RandomIndex(int ArrayLength)
{
    int Random{};
    do
    {
        Random=rand();
    } while(Random>=ArrayLength);
    return Random;    
}

int *RandomArray(int ArrayLength)
{
    int *Array = new int[ArrayLength];
    for (int i = 0; i < ArrayLength; i++)
    {
        Array[i]=rand()%1000;
    }
    return Array;
}

void Swap(int *Array, int First, int Second)
{
    int Temp=Array[First];
    Array[First]=Array[Second];
    Array[Second]=Temp;
    return;
}

void BubbleSort2(int *Array, int ArrayLength)
{
    bool Repeat=false;
    int MaxLength=ArrayLength-1;
    do
    {
        Repeat=false;
        for(int i=0;i<MaxLength;i++)
        {
            if(Array[i]>Array[i+1])
            {
                Repeat=true;
                Swap(Array,i,i+1);
            } 
        }
        MaxLength=MaxLength-1;
    }while(Repeat==true);
    return;    
}

void QuickSort(int* Array, int Left, int Right)
 {

    int pos{};
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

  
        }
        Swap(Array, pos, Left);
        QuickSort(Array, Left, pos - 1);
        QuickSort(Array, pos + 1, Right);

    }

    return;

}

int main()
{
    srand(time(NULL));
    int ArrayLength=1000;
    // for (int i = 0; i < 100; i++)
    // {
    int *Array=RandomArray(ArrayLength);
    BubbleSort2(Array,ArrayLength);
    std::cout<<BinarySearch(Array,ArrayLength,Array[RandomIndex(ArrayLength)]);
    delete[] Array;
    //}
    return 0;
}