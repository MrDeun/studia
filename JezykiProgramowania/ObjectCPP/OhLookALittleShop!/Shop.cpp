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

    void Store()
    {
        int productCount{};
        std::cout<<"Number of products: ";
        std::cin>> productCount;
        Stuff *Products=new Stuff[productCount];
        for (int i = 0; i < productCount; i++)
        {
            std::string StuffName_in;
            float Price;
            std::cout<<"Name of the "<<i+1<<". product: ";
            std::cin>>StuffName_in;
            std::cout<<"Price of the "<<i+1<<". product: ";
            std::cin>>Price;
            Products[i].SetName(StuffName_in);
            Products[i].SetPrice(Price);
        }
        std::cout<<"~~~~Biedronka~~~~"<<std::endl;
        for (int i = 0; i < productCount; i++)
        {
            std::cout<<i+1<<": "<<Products[i]<<std::endl;
        }
        std::cout<<"~~~~~~~~~~~~~~~~~"<<std::endl;

        std::ofstream  storeData("store.txt");
        storeData<<productCount;
        for (int i = 0; i < productCount; i++)
        {
            storeData<<Products[i]<<std::endl;
        }
        storeData.close();
        
        
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
        std::cout<<"Potato is more expensive than Kiwi"<<std::endl;
    if(Potato<Kiwi)
        std::cout<<"Potato is less expensive than Kiwi"<<std::endl;
    Store();
    return 0;


}