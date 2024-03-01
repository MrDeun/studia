#include <iostream>
class A1{
public: 
    A1(){alert();}
    virtual void alert()
    {
        std::cout << "A1 created!\n";
    }
};
class A2{
public: 
    A2(){alert();}
    virtual void alert()
    {
        std::cout << "A2 created!\n";
    }
};
class B1: public A1, public A2{
public: 
    B1(){alert();}
    virtual void alert()
    {
        std::cout << "B1 created!\n";
    }
};
class B2: public A1, public A2{
public: 
    B2(){alert();}
    virtual void alert()
    {
        std::cout << "B2 created!\n";
    }
};
class C: public B1, public B2{
public: 
    C(){alert();}
    virtual void alert()
    {
        std::cout << "B2 created!\n";
    }
};


int main()
{
 C instance;
 return 0;
}
