#include <iostream>
class A1{
public: 
    A1(){alert();}
    virtual void alert()
    {
        std::cout << "A1 created!\n";
    }

    virtual ~A1(){}
};
class A2{
public: 
    A2(){alert();}
    ~A2(){;}
    virtual void alert()
    {
        std::cout << "A2 created!\n";
    }
};
class B1: virtual public A1, virtual public A2{
public: 
    B1(){alert();}
    virtual void alert()
    {
        std::cout << "B1 created!\n";
    }

    
};
class B2: virtual public A1, virtual public A2{
public: 
    B2(){alert();}
    ~B2(){}
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
        std::cout << "C created!\n";
    }
    ~C(){}
};


int main()
{
 C* ptr_instance = new C();
 delete ptr_instance;
 return 0;
}
