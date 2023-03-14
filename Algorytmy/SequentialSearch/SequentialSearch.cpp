#include <iostream>
#include <fstream>
#include <time.h>


float *RandomTable(int Rozmiar)
{
    float *RandomTable = new float[Rozmiar];
    for (int i = 0; i < Rozmiar; i++)
    {
        RandomTable[i]=rand();
    }
    return RandomTable;
}
int SequentialSearch(float *Table, int Rozmiar, int Szukana)
{
    for (int i = 0; i < Rozmiar; i++)
    {
        if (Table[i] == Szukana)
            return i;
    }
    return -1;
}
void Show(float* Table, int Rozmiar)
{
    for (int i = 0; i < Rozmiar; i++)
    {
        std::cout << Table[i] << ", ";
        if (i % 10 == 9)
            std::cout << std::endl;
    }
    std::cout << std::endl;
    return;
}
int LosujIndex(int Rozmiar)
{
    int Random;
    do
    {
       Random=rand();
    } while (Random>=Rozmiar);
    return Random;
    
}
float SequentialSearchStatistics(int max, int Rozmiar)
{
    int Suma=0;
    for(int i=0;i<max;i++)
    {
        float* Table = RandomTable(Rozmiar);
        int Index=LosujIndex(Rozmiar);
        Suma+=SequentialSearch(Table, Rozmiar, Table[Index]);
        delete[] Table;
    }
    return Suma/Rozmiar;
}
void TestSearch()
{
    std::ofstream File("wyszukiwanie.dat");
    for(int i=10;i<1001;i+=10)
    {
        float Medium=SequentialSearchStatistics(100,i);
        File << i << "\t"<<Medium<<"\n" ;
    }
    File << "\n................................................";
    File.close();
}

int main()
{
    srand(time(NULL));
    TestSearch();
    return 0;
    
}