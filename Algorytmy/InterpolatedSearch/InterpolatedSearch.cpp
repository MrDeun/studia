#include<iostream>
#include<fstream>

long long RandomIndex(long long ArrayLength)
{
    long long Random{};
    do
    {
        Random=rand();
    } while(Random>=ArrayLength);
    return Random;    
}

long long *RandomArray(long long ArrayLength)
{
    long long *Array = new long long[ArrayLength];
    for (long long i = 0; i < ArrayLength; i++)
    {
        Array[i]=rand()%1000;
    }
    return Array;
}

void Swap(long long *Array, long long First, long long Second)
{
    long long Temp=Array[First];
    Array[First]=Array[Second];
    Array[Second]=Temp;
    return;
}

void BubbleSort2(long long *Array, long long ArrayLength)
{
    bool Repeat=false;
    long long MaxLength=ArrayLength-1;
    do
    {
        Repeat=false;
        for(long long i=0;i<MaxLength;i++)
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

long long Interpolation(long long* Array,long long Left, long long Right, long long Search)
{
    long long Estimate=Left+(((Search-Array[Left])*(Right-Left))/(Array[Right]-Array[Left]));
    return Estimate;
}

long long InterpolatedSearch(long long *Array,long long ArrayLength, long long Search, double &CompareCount)
{
    long long Left=0,Right=ArrayLength-1,Middle;
    while(Left<=Right)
    {
        Middle=Interpolation(Array,Left,Right,Search);
        if(Middle==Search)
            {CompareCount++;return Search;}
        if(Array[Middle]<Search)
            {CompareCount++;Left=Middle+1;}
        else
            {CompareCount++;Right=Middle-1;}
    }
    return -1;
}

double InterpolatedSearchStatictics(long long ArrayLength,long long Max)
{
    double Summary{},Count{};
    for(long long i=0;i<Max;i++)
    {
        Count=0;
        long long *Array=RandomArray(ArrayLength);
        BubbleSort2(Array,ArrayLength);
        InterpolatedSearch(Array,ArrayLength,Array[RandomIndex(ArrayLength)],Count);
        Summary+=Count;
    }
    return (Summary/Max);
}

void TestInterpolatedSearch()
{
    std::ofstream MyFile("Interpolated_search.dat");
    long long ArrayLength=0;
    for(long long i=0;i<100;i++)
    {
        ArrayLength+=10;
        MyFile<<ArrayLength<<"\t"<<InterpolatedSearchStatictics(ArrayLength,100)<<std::endl;
    }

    return;
}



int main()
{
    srand(time(NULL));
    TestInterpolatedSearch();
    return 0;
}