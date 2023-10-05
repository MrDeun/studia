#include<iostream>
#include<cmath>


class Triangle
{
    private:
    long double Ramie;
    long double Podstawa;
    public:
    long double PoliczPole()
    {
        long double Wysokosc=sqrt((Ramie*Ramie)-(Podstawa*Podstawa)/4);
        long double Pole=0.5*Podstawa*Wysokosc;
        return Pole;
    }
    long double PoliczObwod()
    {
        return 2*Ramie+Podstawa;
    }

    long double GetRamie()
    {
        return Ramie;
    }
    long double GetPodstawa()
    {
        return Podstawa;
    }

    void SetRamie(long double Ramie_in)
    {
        Ramie=Ramie_in;
        return;
    }
    void SetPodstawa(long double Podstawa_in)
    {
        Podstawa=Podstawa_in;
        return;
    }

    Triangle()
    {
        Ramie=0;
        Podstawa=0;
    }
    Triangle(long double Podstawa_in,long double Ramie_in)
    {
        Ramie=0;
        SetRamie(Ramie_in);
        Podstawa=0;
        SetPodstawa(Podstawa_in);
        return;

    }
};

int main()
{
    Triangle Trojkat1(5.0,10.0);
    Triangle *Trojkat2 = new Triangle(322.0,20.0);

    std::cout<<"Trojkat Pierwszy: "<<std::endl;
    std::cout<<"\t Ramie: "<<Trojkat1.GetRamie()<<std::endl;
    std::cout<<"\t Podstawa: "<<Trojkat1.GetPodstawa()<<std::endl;
    std::cout<<"\t Pole: "<<Trojkat1.PoliczPole()<<std::endl;
    std::cout<<"\t Obwod: "<<Trojkat1.PoliczObwod()<<std::endl;

    std::cout<<"Trojkat Drugi: "<<std::endl;
    std::cout<<"\t Ramie: "<<Trojkat2->GetRamie()<<std::endl;
    std::cout<<"\t Podstawa: "<<Trojkat2->GetPodstawa()<<std::endl;
    std::cout<<"\t Pole: "<<Trojkat2->PoliczPole()<<std::endl;
    std::cout<<"\t Obwod: "<<Trojkat2->PoliczObwod()<<std::endl;

    delete Trojkat2;

    return 0;
}