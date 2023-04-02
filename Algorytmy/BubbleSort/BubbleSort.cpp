#include<iostream>
using namespace std;

void Swap(int* Table, int FirstElement, int SecondElement)
{
    int Temp=Table[FirstElement];
    Table[FirstElement]=Table[SecondElement];
    Table[SecondElement]=Temp;
    return;
}

int *RandomTable(int TableLength)
{
    int *Table = new int[TableLength];
    for (int i = 0; i < TableLength; i++)
    {
        Table[i]=rand();
    }
    return Table;
}

void BubbleSort1(int TableLength, int* Table, int* Comparisions, int* Swaps)
{
    bool powtorka = false;
        do
    {
        powtorka=true;
        for (int y = 0; y < TableLength-1; y++)
        {
            if (Table[y] > Table[y + 1])
            {
                Swap(Table,y,y+1);
                *Swaps++;
            }
            *Comparisions++;
        }
    } while (powtorka == true);
}

void BubbleSort2(int TableLength, int* Table, int* Comparisions, int* Swaps)
{
    bool powtorka = false;
        do
    {
        powtorka=true;
        for (int y = 0; y < TableLength-1; y++)
        {
            if (Table[y] > Table[y + 1])
            {
                Swap(Table,y,y+1);
                *Swaps++;
            }
            *Comparisions++;
        }
        TableLength--;
    } while (powtorka == true);
}

int main()
{
    int CompValue=0,SortValue=0;
    int *Table=RandomTable(100);
    int* Comparsions=&CompValue;
    int* Sorts=&SortValue;

    BubbleSort1(100,Table,Comparsions,Sorts);
    cout<<"Statystyki dla pierwszego sortowania:\n"
        <<"Liczba porownan: "<<CompValue<<endl
        <<"Liczba Przestawien"<<SortValue<<endl;

    CompValue=0;
    SortValue=0;
    delete[] Table;
    Table=RandomTable(100);

    BubbleSort2(100,Table,Comparsions,Sorts);
    cout<<"Statystyki dla pierwszego sortowania:\n"
        <<"Liczba porownan: "<<CompValue<<endl
        <<"Liczba Przestawien"<<SortValue<<endl;
    

    return 0;
}