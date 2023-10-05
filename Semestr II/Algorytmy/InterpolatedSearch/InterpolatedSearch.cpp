#include<iostream>
#include<fstream>

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

int *RandomArray(int ArrayLength)
{
    int *Array = new int[ArrayLength];
    for (int i = 0; i < ArrayLength; i++)
    {
        Array[i]=rand()%1000;
    }
    return Array;
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
    int Numerator = (Search - Array[Left])*(Right-Left);
    int Denominator = Array[Right]-Array[Left];
    int Returnal = Left + (Numerator/Denominator);
    return Returnal;
}

int InterSearch(int* Array, int ArrayLength, int Search,double &Count)
{
    int Left=0, Right=ArrayLength-1,Middle;
    while(Left<=Right)
    {
        Middle=Interpolation(Array,Left,Right,Search);
        if(Array[Middle]==Search)
            {Count++;return Middle;}
        else if(Array[Middle]<Search)
            {Count++;Left=Middle+1;}
        else
            Right=Middle-1;
        
    }
    return -1;
}

double InterSearchStatictics(int ArrayLength,int Max)
{
    double Summary{},Count{};
    for(int i=0;i<Max;i++)
    {
        Count=0;
        int *Array=RandomArray(ArrayLength);
        BubbleSort2(Array,ArrayLength);
        InterSearch(Array,ArrayLength,Array[RandomIndex(ArrayLength)],Count);
        Summary+=Count;
    }
    return (Summary/Max);
}

void TestInterSearch()
{
    std::ofstream MyFile("inter_search.dat");
    int ArrayLength=0;
    for(int i=0;i<100;i++)
    {
        ArrayLength+=10;
        MyFile<<ArrayLength<<"\t"<<InterSearchStatictics(ArrayLength,100)<<std::endl;
    }

    return;
}

int main()
{
    TestInterSearch();
    return 0;
}