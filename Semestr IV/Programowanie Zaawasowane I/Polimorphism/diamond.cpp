#include<iostream>

class A{
    public:
        A() {std::cout << "A created!\n"; }
        virtual ~A() {std::cout << "A destroyed\n";}
};
class B : public A{
    public:
        B() {std::cout << "B created!\n"; }
        virtual ~B() {std::cout << "B destroyed\n";}
};
class C : public A{
    public:
        C() {std::cout << "C created!\n"; }
        virtual ~C() {std::cout << "C destroyed\n";}
};
class D : public C, public B{
    public:
        D() {std::cout << "D created!\n"; }
        virtual ~D() {std::cout << "D destroyed\n";}
};

int main()
{
    D* ptr_instance = new D();
    delete ptr_instance;
    return 0;
}