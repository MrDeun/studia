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

void Swap(int *Array, int First, int Second)
{
    int Temp=Array[First];
    Array[First]=Array[Second];
    Array[Second]=Temp;
    return;
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

long double BubbleSort1(int *Array, int ArrayLength)
{
    int Comparision=0;
    bool Repeat=false;
    do
    {
        Repeat=false;
        for(int i=0;i<ArrayLength-1;i++)
        {
            if(Array[i]>Array[i+1])
            {
                Repeat=true;
                Swap(Array,i,i+1);
            }
            Comparision++;   
        }
    }while(Repeat==true);
    return Comparision;    
}

long double BubbleSort2(int *Array, int ArrayLength)
{
    int Comparision=0;
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
            Comparision++;   
        }
        MaxLength=MaxLength-1;
    }while(Repeat==true);
    return Comparision;    
}

long double BubbleSort1Statistics(int ArrayLength, int MaxRepeat)
{
    long double Summary=0.0;
    for (int i = 0; i < MaxRepeat; i++)
    {
        int *Array=RandomArray(ArrayLength);
        Summary+=BubbleSort1(Array,ArrayLength);
        delete[] Array;
    }

    return (Summary/MaxRepeat);
    
}

long double BubbleSort2Statistics(int ArrayLength, int MaxRepeat)
{
    long double Summary=0.0;
    for (int i = 0; i < MaxRepeat; i++)
    {
        int *Array=RandomArray(ArrayLength);
        Summary+=BubbleSort2(Array,ArrayLength);
        delete[] Array;
    }

    return (Summary/MaxRepeat);
    
}

void TestBubbleSort1()
{
    std::ofstream File("BubbleSort1.dat");
    int ArrayLength=0;
    for(int i=0;i<100;i++)
    {
        ArrayLength+=10;
        long double Result=BubbleSort1Statistics(ArrayLength,100);
        File<<ArrayLength<<"\t\t\t"<<Result<<std::endl;
    }
    File<<"\n\n=========================================";
    File.close();
    return;

}

void TestBubbleSort2()
{
    std::ofstream File("BubbleSort2.dat");
    int ArrayLength=0;
    for(int i=0;i<100;i++)
    {
        ArrayLength+=10;
        long double Result=BubbleSort2Statistics(ArrayLength,100);
        File<<ArrayLength<<"\t\t\t"<<Result<<std::endl;
    }
    File<<"\n\n=========================================";
    File.close();
    return;

}

int main()
{
    TestBubbleSort1();
    TestBubbleSort2();


    return 0;
}