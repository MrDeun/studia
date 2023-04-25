#include<iostream>
#include<fstream>

class Stuff
{
    float Price;
    std::string StuffName;

    public: 
    Stuff(std::string StuffName_in="Unspecified", float Price_in=0.0):StuffName(StuffName_in),Price(Price_in){};

    void SetPrice(float Price_in)
    {
        Price=Price_in;
        return;
    }

    void SetName(std::string StuffName_in)
    {
        StuffName=StuffName_in;
        return;
    }

    float GetPrice(){return Price;}
    std::string GetName(){return StuffName;}

    Stuff& operator+=(float Price_Raise)
    {
        Price=Price+Price_Raise;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& Os_in, Stuff& Stuff_in);

    bool operator>(Stuff& stuff_in)
    {
        return (this->Price>stuff_in.Price);
    }
};

    std::ostream& operator<<(std::ostream& Os_in, Stuff& Stuff_in)
    {
        Os_in<<Stuff_in.StuffName<<": "<<Stuff_in.Price;
        return Os_in;
    }

    Stuff& operator-=(Stuff& stuff_in, float Val_Discount)
    {
        stuff_in.SetPrice(stuff_in.GetPrice()-Val_Discount);
        return stuff_in;
    }

    bool operator<(Stuff &stuff_in1,Stuff &stuff_in2)
    {
        return(stuff_in1.GetPrice()<stuff_in2.GetPrice());
    }

int main()
{
    Stuff Potato("Potato",10.5);
    std::cout<<Potato<<std::endl;
    Potato+=3.0;
    std::cout<<Potato<<std::endl;
    Potato-=5.0;
    std::cout<<Potato<<std::endl;
    Stuff Kiwi("Kiwi",11.0);
    if(Potato>Kiwi)
        std::cout<<"Potato is more expensive than Kiwi";
    if(Potato<Kiwi)
        std::cout<<"Potato is less expensive than Kiwi";
    return 0;


}