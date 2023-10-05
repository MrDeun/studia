#include<iostream>

class Mother
{
    private:
        float x{1};
    protected:
        float y{2};

    public:
        float z{3};
        float GetX(){return x;}
        float GetY(){return y;}
        Mother(){std::cout<<"Mother's constructor";}
        ~Mother(){std::cout<<"Mother's destructor";}
        void ShowM(){std::cout<<"X:"<<x<<" Y:"<<y<<" Z:"<<z<<std::endl;}   
};

class Daughter : protected Mother
{
    public:
    float t{4};
    Daughter(){std::cout<<"Daughter's constructor"<<std::endl;}
    ~Daughter(){std::cout<<"Daughther's destructor"<<std::endl;}
    void ShowD(){std::cout<<"X:"<<GetX()<<" Y:"<<y<<" Z:"<<z<<" T: "<<t<<std::endl;}
};


int main()
{
    Mother m;
    m.ShowM();
    std::cout<<"x="<<m.GetX()<<std::endl;
    std::cout<<"y="<<m.GetY()<<std::endl;
    std::cout<<m.z<<std::endl;

    Daughter *d = new Daughter();
    d->ShowM();
    d->ShowD();
    delete d;
    return 0;

    return 0;
}