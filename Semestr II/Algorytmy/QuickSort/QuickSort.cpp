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



double QuickSortStatictics(double Max, int Length)
{
    int Summary{};
    int Compares=0;
    for(int i=0;i<Max;i++)
    {
        Compares=0;
        int *Array=RandomArray(Length);
        QuickSort(Array,0,Length-1, Compares);
        Summary+=Compares;
        delete[] Array;
    }
    
    double Result= Summary/Max;
    return Result;

}
  
void TestQuickSort()
{
    std::ofstream MyFile("quicksort.dat");
    int Length{0};
    for (int i = 0; i < 100; i++)
    {
        Length+=10;
        double Result=QuickSortStatictics(100,Length);
        MyFile<<Length<<"\t"<<Result<<std::endl;
    }
    MyFile<<".......................................";
    MyFile.close();
}

int main()
{
    TestQuickSort();
    srand(time(NULL));
    return 0;
}