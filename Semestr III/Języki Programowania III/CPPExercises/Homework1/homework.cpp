#include <iostream>
#include <numeric>

int GreatestCommonDivisor(int firstNumber, int secondNumber)
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

int LeastCommonMultipication(int firstNumber, int secondNumber)
{
    return (firstNumber*secondNumber)/GreatestCommonDivisor(firstNumber,secondNumber);
}


int main()
{
    bool firstResult=GreatestCommonDivisor(5,6)==std::gcd(5,6);
    bool secondResult=LeastCommonMultipication(5,6)==std::lcm(5,6);

    std::cout<<firstResult<<"\n"<<secondResult;

    return 0;
}