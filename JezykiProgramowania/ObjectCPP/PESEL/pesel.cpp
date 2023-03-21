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

    int GetYear()
    {
        int year=(PESEL/1000000000ll)+1900;
        int century=((PESEL/10000000ll)%100ll)/20;
        if(century==4) year-=100;
        if(century<=3) year+=100*century;
        return year;
    }

    int GetMonth()
    {
        return ((PESEL/10000000ll)%100ll)%20;
    }

    int GetDay()
    {
        return ((PESEL/100000ll)%10000ll);
    }

    bool IsMale()
    {
        if(((PESEL/10ll)%1000000000ll)%2==1)
            return true;
        else
            return false;
    }

    static int GetControlValue(long long PESEL_in);
    bool IsCorrect()
    {
       if(GetControlValue(PESEL)==(PESEL%10)) return true;
       return false; 
    }
    void ShowAll();


};

int Person::GetControlValue(long long PESEL_in)
{
    int Summary{};
    PESEL_in/=10;
    Summary+=3*(PESEL_in%10);PESEL_in/=10;
    Summary+=1*(PESEL_in%10);PESEL_in/=10;
    for (int i = 0; i < 2; i++)
    {
    Summary+=9*(PESEL_in%10);PESEL_in/=10;
    Summary+=7*(PESEL_in%10);PESEL_in/=10;
    Summary+=3*(PESEL_in%10);PESEL_in/=10;
    Summary+=1*(PESEL_in%10);PESEL_in/=10;
    }

    int ControlValue{};
    ControlValue=(10-Summary%10)%10;
    return ControlValue;
}

void Person::ShowAll()
{
    cout<<"Name&Surname: "<<name<<" "<<surname<<endl;
    cout<<"PESEL: "<<PESEL<<" "<<(IsCorrect()?"Valid":"Invalid")<<endl;
    cout<<"Gender: "<<(IsMale()?"Male":"Female")<<endl;
    cout<<"Birthday(DD-MM-YYYY): "<<GetDay()<<"."<<GetMonth()<<"."<<GetYear()<<endl;
    return;
}

int main()
{
    cout<<"Number of bits in int: "<<8*sizeof(int)-1<<endl;
    cout<<"Number of bits in long: "<<8*sizeof(long)-1<<endl;
    cout<<"Number of bits in long long: "<<8*sizeof(long long)-1;
    cout<<"Number of bits needed: "<<log(1.e11-1)/log(2);
    return 0;
}