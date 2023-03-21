#include<iostream>
#include<cstdlib>
#include<fstream>
int *RandomTable(int TableLength)
{
    int *Table = new int[TableLength];
    for (int i = 0; i < TableLength; i++)
    {
        Table[i]=rand();
    }
    return Table;
}

int SequentialSearch(int *Table, int TableLength, int SearchItem)
{
    for(int i=0;i<TableLength;i++)
    {
        if(SearchItem==Table[i])
            return i;
    }
    return -1;
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

int RandomIndex(int TableLength)
{
    int Random{};
    do
    {
        Random=rand();
    } while(Random>=TableLength);
    return Random;    
}

double SequentialSearchStatistics(int Max,int TableLength)
{
    int Suma=0,Index{};
    int *Table;
    for(int i=0;i<Max;i++)
    {
        Table=RandomTable(TableLength);
        Index=RandomIndex(TableLength);
        Suma+=SequentialSearch(Table,TableLength,Table[Index]);
    }
    double Result{}; 
    Result=(Suma/100.00);
    return Result;
}

void TestSearch()
{
    std::ofstream File("wyszukiwanie.dat");
    double SequentialResult{};
    int TableLength=0;
    for(int i=0;i<100;i++)
    {
        TableLength+=10;
        SequentialResult=SequentialSearchStatistics(100,TableLength);
        File<<TableLength<<"\t\t"<<SequentialResult<<"\n";
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