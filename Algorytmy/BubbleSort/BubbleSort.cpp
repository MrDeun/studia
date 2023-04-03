#include<iostream>
#include<cstdlib>
using namespace std;

int *RandomTable(int TableLength)
{
    int *Table = new int[TableLength];
    for (int i = 0; i < TableLength; i++)
    {
        Table[i]=rand()%25;
    }
    return Table;
}

void ShowTable(int *Table, int TableLength)
{
    system("CLS");
    for(int i=0;i<TableLength;i++)
    {
        std::cout<<Table[i]<<" ";
        if(i%10==9)
            std::cout<<"\n";
    }
    system("PAUSE");
}



void Swap(int *Table, int i)
{
    int Temp=Table[i];
    Table[i]=Table[i+1];
    Table[i+1]=Temp;
    return;
}

void BubbleSort1(int *Table, int TableSize)
{
    bool Repeat=false;
    do
    {
        Repeat=false;
        for(int i=0;i<TableSize-1;i++)
        {
            if(Table[i]>Table[i+1])
            {
                Swap(Table,i);
                Repeat=true;
            }
        }

    }while(Repeat);
    return;
}

int main()
{
    int TabSize=10;
    int *Table=RandomTable(10);
    ShowTable(Table,TabSize);
    BubbleSort1(Table,TabSize);
    ShowTable(Table,TabSize);
    return 0;
}