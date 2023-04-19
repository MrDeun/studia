#include<iostream>

class A
{
    friend class B;
    private:
    int i=20;
};

class B
{
    friend class D;
    A ObjectA;
    public:
    void Change(int Val_in)
    {
        ObjectA.i=Val_in;
    }
};

class C
{
    A ObjectA;
    public:
    void Change(int Val_in)
    {
        ObjectA.i=Val_in;
    }
};

class D
{
    A ObjectA;
    public:
    void Change(int Val_in)
    {
        ObjectA.i=Val_in;
    }
};


int main()
{
    return 0;
}