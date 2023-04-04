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

void ShowArray(int *Array, int ArrayLength)
{
    system("CLS");
    for(int i=0;i<ArrayLength;i++)
    {
        std::cout<<Array[i]<<" ";
        if(i%10==9)
            std::cout<<std::endl;
    }
    system("PAUSE");
}



void Swap(int *Array, int FirstPostion, int SecondPosition)
{
    int Temp=Array[FirstPostion];
    Array[FirstPostion]=Array[SecondPosition];
    Array[FirstPostion]=Temp;
    return;
}

double BubbleSort1(int *Array, int ArraySize)
{
    double Comparision=0;
    bool Repeat=false;
    do
    {
        Repeat=false;
        for(int i=0;i<ArraySize-1;i++)
        {
            if(Array[i]>Array[i+1])
            {
                Swap(Array,i,i+1);
                Repeat=true;
            }
            Comparision++;
        }

    }while(Repeat==true);
    return Comparision;
}

double BubbleSort1Statistics(int Max,int ArrayLength)
{
    double Sum{};
    for (int i = 0; i < Max; i++)
    {
        int *Array=RandomArray(ArrayLength);
        Sum+=BubbleSort1(Array,ArrayLength);
        delete[] Array;
    }

    return (Sum/(double)Max);
    
}

void TestBubbleSort1()
{
    std::ofstream File("BubbleSort1.dat");
    double BubbleSortResult{};
    int ArrayLength=0;
    for(int i=0;i<10;i++)
    {
        ArrayLength+=10;
        BubbleSortResult=BubbleSort1Statistics(100,ArrayLength);
        File<<ArrayLength<<"\t\t"<<BubbleSortResult<<"\n";
    }
    File.close();
    return;
}
// void BubbleSort2(int *Array, int ArraySize)
// {
//     bool Repeat=false;
//     int MaxArrayLoop=ArraySize-1;
//     do
//     {
//         Repeat=false;
//         for(int i=0;i<MaxArrayLoop;i++)
//         {
//             if(Array[i]>Array[i+1])
//             {
//                 Swap(Array,i);
//                 Repeat=true;
//             }
//         }
//     MaxArrayLoop=MaxArrayLoop-1;
//     }while(Repeat);
//     return;
// }

int main()
{
    srand(time(NULL));

    // ShowArray(Array,TabSize);
    TestBubbleSort1();
    // ShowArray(Array,TabSize);
    std::cout<<"Skonczona generacja danych"<<std::endl;

    return 0;
}