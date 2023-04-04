#include<iostream>
#include<cstdlib>
#include<fstream>
int *RandomArray(int ArrayLength)
{
    int *Array = new int[ArrayLength];
    for (int i = 0; i < ArrayLength; i++)
    {
        Array[i]=rand();
    }
    return Array;
}

int SequentialSearch(int *Array, int ArrayLength, int SearchItem)
{
    for(int i=0;i<ArrayLength;i++)
    {
        if(SearchItem==Array[i])
            return i;
    }
    return -1;
}

void ShowArray(int *Array, int ArrayLength)
{
    system("CLS");
    for(int i=0;i<ArrayLength;i++)
    {
        std::cout<<Array[i]<<" ";
        if(i%10==9)
            std::cout<<"\n";
    }
    system("PAUSE");
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

double SequentialSearchStatistics(int Max,int ArrayLength)
{
    int Suma=0,Index{};
    int *Array;
    for(int i=0;i<Max;i++)
    {
        Array=RandomArray(ArrayLength);
        Index=RandomIndex(ArrayLength);
        Suma+=SequentialSearch(Array,ArrayLength,Array[Index]);
    }
    double Result{}; 
    Result=(Suma/100.00);
    return Result;
}

void TestSearch()
{
    std::ofstream File("wyszukiwanie.dat");
    double SequentialResult{};
    int ArrayLength=0;
    for(int i=0;i<100;i++)
    {
        ArrayLength+=10;
        SequentialResult=SequentialSearchStatistics(100,ArrayLength);
        File<<ArrayLength<<"\t\t"<<SequentialResult<<"\n";
    }
    File.close();
    return;
}

int main()
{
    srand(time(NULL));
    TestSearch();
    return 0;
}