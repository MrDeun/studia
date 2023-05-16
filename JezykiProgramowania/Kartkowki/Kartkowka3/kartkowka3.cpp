#include<iostream>
#include<cmath>

class Complex
{
    private:
        double Real;
        double Imaginative;
    public:
    Complex(double Real_in,double Imaginative_in)
    {
        Real=Real_in;
        Imaginative=Imaginative_in;
    }

    ~Complex(){}

    void SetReal(double Real_in){Real=Real_in;}
    void SetImaginative(double Imaginative_in){Imaginative=Imaginative_in;}
    double GetReal(){return Real;}
    double GetImaginative(){return Imaginative;}

    friend std::ostream& operator<<(std::ostream& StreamOut,Complex& Complex_in);

    double Modulo()
    {
        double Temp=(Real*Real)+(Imaginative*Imaginative);
        return sqrt(Temp);
    }

    Complex& operator+=(Complex& Complex_in)
    {
        Real+=Complex_in.Real;
        Imaginative+=Complex_in.Imaginative;
        return *this;
    }

    bool operator<(Complex& Complex_in)
    {
        return Modulo()<Complex_in.Modulo();
    }


};

    std::ostream& operator<<(std::ostream& Os_in, Complex& Complex_in)
    {
        Os_in<<"Z="<<Complex_in.GetReal()<<"+i"<<Complex_in.GetImaginative()<<",\t"<<"Mod(z)="<<Complex_in.Modulo();
        return Os_in;
    }


int main()
{
    Complex z1(1.0,5.0),z2(22.0,3.1416);

    std::cout<<"z1= "<<z1<<std::endl;
    std::cout<<"z2= "<<z2<<std::endl;

    z1+=z2;
    std::cout<<"z1= "<<z1<<std::endl;

    if(z1<z2)
        std::cout<<"z1<z2";
    else
        std::cout<<"z1>=z2";

    return 0;
}