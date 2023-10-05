#include<iostream>
#include<fstream>

int BinarySearch(int* Array,int ArrayLength, int Search,double &CompareCount)
{
    int Left=0,Right=ArrayLength-1;
    while (Left<=Right)
    {
        int Middle=(Left+Right)/2;
        if(Array[Middle]==Search)
            {CompareCount++;return Search;}
        if(Array[Middle]<Search)
            {CompareCount++;Left=Middle+1;}
        else
            {CompareCount++;Right=Middle-1;}
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

double BinarySearchStatictics(int ArrayLength,int Max)
{
    double Summary{},Count{};
    for(int i=0;i<Max;i++)
    {
        Count=0;
        int *Array=RandomArray(ArrayLength);
        BubbleSort2(Array,ArrayLength);
        BinarySearch(Array,ArrayLength,Array[RandomIndex(ArrayLength)],Count);
        Summary+=Count;
    }
    return (Summary/Max);
}

void TestBinarySearch()
{
    std::ofstream MyFile("binary_search.dat");
    int ArrayLength=0;
    for(int i=0;i<100;i++)
    {
        ArrayLength+=10;
        MyFile<<ArrayLength<<"\t"<<BinarySearchStatictics(ArrayLength,100)<<std::endl;
    }

    return;
}


int main()
{
    srand(time(NULL));
    TestBinarySearch();
    return 0;
}