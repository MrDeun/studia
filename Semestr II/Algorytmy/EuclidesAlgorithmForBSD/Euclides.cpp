#include<iostream>
#include<windows.h>
int EuclidesAlgorithm(int First, int Second)
{
    int Modulo{0};
    while (Second>0)
    {
        Modulo=First%Second;
        First=Second;
        Second=Modulo;
    }
    return First;
    
}

int main()
{
    int First,Second;
    std::cout<<"Podaj dwie liczby a ja ci powiem jakich jest ich najwiekszy wspolny dzielnik: ";
    std::cin>>First>>Second;
    std::cout<<"Najwiekszych ich wspolny dzielnik to: "<<EuclidesAlgorithm(First,Second);

    return 0;
}