#include <iostream>
#include<Windows.h>
struct Karta
{
    int Wartosc;
    int Kolor;
    bool Wyciagnieta=false;
    std::string RozszyfrujKolor(int Kolor)
    {
        switch (Kolor)
        {
        case 0:return "Serce";
        case 1:return "Wino";
        case 2:return "Zoladz";
        case 3:return "Diament";
        default:return "ERROR";
        }
    }

    std::string RozszyfrujWartosc(int Kolor)
    {
        switch (Kolor)
        {
        case 0:return "9";
        case 1:return "10";
        case 2:return "J";
        case 3:return "Q";
        case 4:return "K";
        case 5:return "A";
        default:return "ERROR";
        }
    }

};

void Generate(Karta *Deck)
{
    for (int Licznik = 0; Licznik < 4; Licznik++)
    {
        for (int LicznikDrugi = 0; LicznikDrugi < 6; LicznikDrugi++)
            Deck[LicznikDrugi + (6 * Licznik)].Kolor = Licznik % 4;
    }

    for (int Licznik = 0; Licznik < 24; Licznik++)
        Deck[Licznik].Wartosc = Licznik % 6;
    return;


}
void Show(Karta* Deck, int Rozmiar)
{
    //system("CLS");
    std::cout << std::endl;
    for (int Licznik = 0; Licznik < Rozmiar; Licznik++)
    {
        std::cout << Deck[Licznik].RozszyfrujKolor(Deck[Licznik].Kolor);
        std::cout << Deck[Licznik].RozszyfrujWartosc(Deck[Licznik].Wartosc);
        std::cout << "    ";

        if (Licznik % 6 == 5)
            std::cout << std::endl;
    }
    return;
}

void Randomize(Karta* Deck, int DeckSize)
{
    int currentIndex=DeckSize,randomIndex;

    while(currentIndex!=0)
    {
        randomIndex = rand()%currentIndex;
        currentIndex--;
        std::swap(Deck[randomIndex],Deck[currentIndex]);
    }

    return;
}

void GiveTheCard()
{
    
}

int main()
{
    const int Rozmiar = 24;
    Karta *Deck = new Karta[Rozmiar];
    Generate(Deck);
    Show(Deck, Rozmiar);
    Randomize(Deck, Rozmiar);
    Show(Deck, Rozmiar);
    system("PAUSE");
    return 0;
}