#include<iostream>
#include<fstream>

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

int Interpolation(int* Array,int Left, int Right, int Search)
{
    int Estimate = Left + ((Search - Array[Left]) * (Right - Left) / (Array[Right] - Array[Left]));
    return Estimate;
}

int InterpolatedSearch(int *Array,int ArrayLength, int Search, double &CompareCount)
{
    int Left=0,Right=ArrayLength-1,Middle;
    while ((Array[Right] != Array[Left]) && (Search >= Array[Left]) && (Search <= Array[Right]))
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

double InterpolatedSearchStatictics(int ArrayLength,int Max)
{
    double Summary{},Count{};
    for(int i=0;i<Max;i++)
    {
        Count=0;
        int *Array=RandomArray(ArrayLength);
        BubbleSort2(Array,ArrayLength);
        InterpolatedSearch(Array,ArrayLength,Array[RandomIndex(ArrayLength)],Count);
        Summary+=Count;
    }
    return (Summary/Max);
}

void TestInterpolatedSearch()
{
    std::ofstream MyFile("Interpolated_search.dat");
    int ArrayLength=0;
    for(int i=0;i<100;i++)
    {
        ArrayLength+=10;
        MyFile<<ArrayLength<<"\t"<<InterpolatedSearchStatictics(ArrayLength,100)<<std::endl;
    }

    return;
}



int main()
{
    srand(time(NULL));
    double Count{};
    //TestInterpolatedSearch();
    int *SingleArray = RandomArray(50);
    BubbleSort2(SingleArray,50);
    std::cout<<InterpolatedSearch(SingleArray,50,SingleArray[RandomIndex(30)],Count);
    return 0;
}