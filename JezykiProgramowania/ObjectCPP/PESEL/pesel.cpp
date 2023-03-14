#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>

using namespace std;

class Person
{
    private:
        char* name;
        char* surname;
        long long PESEL;
    public:
        void SetName(const char* name_in)
        {
            if(name) /*=>*/ delete[] name;
            int n=strlen(name_in);
            name = new char[n+1];
            strcpy(name,name_in);
            return;
        }
        void SetSurname(const char *surname_in)
        {
            if(surname) delete[] surname;
            int n=strlen(surname_in);
            surname = new char[n+1];
            strcpy(surname,surname_in);
            return;
        }
        void SetPESEL(const long long PESEL_in)
        {
            PESEL=PESEL_in;
            return;
        }



};



int main()
{


    return 0;
}