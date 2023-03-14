// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



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
        default:return "Error";
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
        default:return "Error";
        }
    }

    void Generate(int Rozmiar, Karta* Deck)
    {
        for (int Licznik = 0; Licznik < 4; Licznik++)
        {
            for (int LicznikDrugi = 0; LicznikDrugi < 6; LicznikDrugi++)
             Deck[LicznikDrugi + (6 * Licznik)].Kolor = Licznik % 4;
        }

        for (int Licznik = 0; Licznik < Rozmiar; Licznik++)
            Deck[Licznik].Wartosc = Licznik % 6;
        return;
    }

};

class Player
{
    public:
    Karta *Hand;

    void Dobierz(Karta *Hand, Karta *Deck)
    {  
        int i=0,j=0;
        while(Deck[i].Wyciagnieta)
            i++;
        while(!Hand[j].Wyciagnieta)
            j++;
        Deck[i].Wyciagnieta=true;
        Hand[j]=Deck[j];        
        return;
    }     
};


void Show(Karta* Deck, int Rozmiar)
{
    std::cout << std::endl;
    for (int Licznik = 0; Licznik < Rozmiar; Licznik++)
    {
        std::cout << Deck[Licznik].RozszyfrujKolor(Deck[Licznik].Kolor);
        std::cout << Deck[Licznik].RozszyfrujWartosc(Deck[Licznik].Wartosc);
        std::cout << "    ";

        if (Licznik % 4 == 3)
            std::cout << std::endl;
    }
    return;
}


int main()
{
    const int Rozmiar = 24;
    Karta *Deck = new Karta[Rozmiar];
    Deck->Generate(Rozmiar, Deck);
    Show(Deck, Rozmiar);
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
