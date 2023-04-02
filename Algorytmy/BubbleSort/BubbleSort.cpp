#include<iostream>
#include<cstdlib>
using namespace std;

int *RandomTable(int TableLength)
{
    int *Table = new int[TableLength];
    for (int i = 0; i < TableLength; i++)
    {
        Table[i]=rand();
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


void Swap(int *First, int *Second)
{
    int Temp=*Second;
    *Second=*First;
    *First=Temp;
    return;

}

void BubbleSort1(int *Tab, int TabSize)
{
    bool Repeat=false;
    do
    {
    
        for(int i=0;i<TabSize-1;i++)
        {
            if(Tab[i]>Tab[i+1])
            {
                swap(Tab[i],Tab[i+1]);
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