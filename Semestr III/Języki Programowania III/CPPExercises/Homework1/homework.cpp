export module dlib;

#include <iostream>
#include <numeric>
export namespace dlib
{
     int gcd(int firstNumber, int secondNumber)
    {
        int Temporary;
        while(secondNumber)
        {
            Temporary = secondNumber;
            secondNumber = firstNumber % secondNumber;
            firstNumber = Temporary;
        }
        return firstNumber;
}

     int lcm(int firstNumber, int secondNumber)
    {
        return (firstNumber*secondNumber)/gcd(firstNumber,secondNumber);
    }
}

int main()
{
    bool firstResult=dlib::gcd(5,6)==std::gcd(5,6);
    bool secondResult=dlib::lcm(5,6)==std::lcm(5,6);

    std::cout<<firstResult<<"\n"<<secondResult;

    return 0;
}