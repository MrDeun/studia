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

        Person()
        {
            name=0; SetName("");
            surname=0; SetSurname("");
            SetPESEL(0);
        }
        Person(const char* name_in, const char* surname_in, const long long PESEL_in)
        {
            name=0; SetName(name_in);
            surname=0; SetSurname(surname_in);
            SetPESEL(PESEL_in);
        }
        ~Person()
        {
            delete[] name;
            delete[] surname;
            PESEL=0ll;
        }

    int GetYear(const long long PESEL_in)
    {
        int year=(PESEL_in/1000000000ll)+1900;
        int century=((PESEL/10000000ll)%100ll)/20;
        if(century==4) year-=100;
        if(century<=3) year+=100*century;
        return year;
    }

    int GetMonth(const long long PESEL_in)
    {
        return ((PESEL/10000000ll)%100ll)%20;
    }



};



int main()
{
    cout<<"PROGRAM OK";
    return 0;
}