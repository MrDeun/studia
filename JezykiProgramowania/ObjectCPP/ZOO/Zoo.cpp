#include<iostream>
#include<cstring>
class Animal
{
    private:
        int LegCount;
    protected:
        float Age;
        std::string Name;
    public:
        float Weight;
        void SetLegsCount(int LegCount_in)
        {
            LegCount=LegCount_in;
            return;
        }
        Animal(std::string Name_in)
        {
            LegCount=0;Age=0;Weight=0;
            Name=Name_in;
        }
        virtual ~Animal(){}
        void virtual Describe()
        {
            std::cout<<"Animal: "<<Name<<", "<<LegCount<<" leg(s), weight: "
            <<Weight<<"kg, age: "<<Age<<" year(s)"<<std::endl;
        }
        void Sleep()
        {
            std::cout<<"The animal is sleeping now..."<<std::endl;
            return;
        }
};

class Cat : public Animal
{
    public:
        std::string Colornation;
        Cat(std::string Cat_name):Animal(Cat_name)
        {
            Name=Cat_name;
            SetLegsCount(4);
            Colornation="None";
            std::cout<<"A new Cat was created!"<<std::endl;
            return;
        }
        ~Cat()
        {
            std::cout<<"A cat was annihilated... you monster."<<std::endl;
            return;
        }
        void Purr()
        {
            std::cout<<"\'Mraaaaaaaau\'"<<std::endl;
            return;
        }
        void Describe()
        {
            Animal::Describe();
            std::cout<<"The cat has "<<Colornation<<" coloranion."<<std::endl;
            return;
        }
};

class Bird : public Animal
{
    public:
    void Fly()
    {
        std::cout<<"The bird is flying"<<std::endl;
    }

    Bird(std::string Name_in):Animal(Name_in)
    {
        Name=Name_in;
        SetLegsCount(2);
        std::cout<<"A new bird has been created"<<std::endl;
    }
    ~Bird()
    {
        std::cout<<"A bird has been destroyed"<<std::endl;
        return;
    }

};

void Eat(Animal *who, Animal* whom)
{
    who->Describe();
    std::cout<<"is eating"<<std::endl;
    whom->Describe();
    who->Weight+=whom->Weight;
    delete whom;  
}

int main()
{ 
    Animal *Cow = new Animal("Mucka");
    Cow->Weight=1000.0;
    Cow->Describe();
    Cow->Sleep();
    delete Cow;

    Cat *cat= new Cat("Rudy");
    cat->Weight=8.0;
    cat->Colornation="Ginger";
    cat->Describe();
    cat->Sleep();
    cat->Purr();

    Bird *Parrot=new Bird("Ambrozy");
    Parrot->Weight=2.0;
    Parrot->Describe();

    std::cout<<"~~~The Dinner has begun~~~~"<<std::endl;
    Eat(cat,Parrot);
    cat->Describe();
    delete cat;

    return 0;
}