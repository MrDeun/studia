#include <iostream>

float *RandomTable(int Rozmiar)
{
    float *RandomTable = new float[Rozmiar];
    int Potencjalna;
    for (int i = 0; i < Rozmiar; i++)
    {
        RandomTable[i]=rand();
    }
    return RandomTable;
}

bool Search(float *Table, int Rozmiar, int Szukana)
{
    for (int i = 0; i < Rozmiar; i++)
    {
        if (Table[i] == Szukana)
            return true;
    }
    return false;
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

int main()
{
    srand(time(NULL));
    int Rozmiar;
    std::cin >> Rozmiar;
    float *Table = RandomTable(Rozmiar);
    Show(Table, Rozmiar);
    int Szukana;
    std::cin >> Szukana;
    std::cout << "Czy w tabeli jest szukana liczba? " << Search(Table, Rozmiar, Szukana);
    return 0;
    
}