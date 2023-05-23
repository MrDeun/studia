#include<iostream>
#include<string.h>

class myString()
{
    private:
        char *chars;
        int size;
    public:
    void Set(const char* string_in)
    {
        if(chars)
            delete[] chars;
        size=strlen(string_in);
        chars=new char[size+1];
        strcpy(chars,string_in);
    }

    myString(const char* chars_in)
    {
        chars=0;
        Set(chars_in);
    }

        myString()
    {
        chars=0;
        string=0;
    }
    myString(myString &str_in);
    ~myString(){}
        if(chars) delete[] chars;

    int GetSize()
    {
        return size+1;
    }

    friend ostream& operator<<(ostream& os_in,myString& mystr_in);
    char &operator[](int Index){return chars[Index];}
    myString &operator=(mystring& mystr_in);
    myString &operator+=(mystring& mystr_in);
    myString &operator+(mystring& mystr_in);

};

myString& myString::operator=(myString& mystr_in)
{
    if(this==&mystr_in)return (*this);
    Set(mystr_in.chars);
    size=mystr_in.size;
    return(*this);
}

myString& myString::operator+=(myString& mystr_in)
{
    char *Chars_Temp=new char[size+mystr_in.size+1]
    for(int i=0;i<size;i++)
        Chars_Temp[i]=chars[i];
    for(int i=0;i<mystr_in;i++)
        Chars_Temp[i+size]=mystr_in.chars[i];

    delete[] chars;
    chars=Chars_Temp;
    size+=mystr_in.size;

    return (*this);
}

myString& myString::operator+(myString& mystr_in)
{
    myString *mystr_tmp=new myString[chars];
    *mystr_tmp+=mystr_in;
    return(*mystr_tmp);
}

ostream &operator<<(ostream& os_in, myString& mystr_in)
{
    os_in<<mystr_in.chars;
    return *os_in;
}

istream &operator>>(istream& is_in, myString& mystr_in)
{
    char StaticArray[256];
    is_in.getline(StaticArray,256);
    mystr_in.Set(StaticArray);
    return *is_in;
}

myString::myString(myString& str_in)
{
    chars=0;
    Set(str_in.chars);
}

int count_ch(mystring mstr_in, char char_in)
{
    int n=0;
    for(int i=0;i<mstr_in.GetSize();i++)
    {
        if(ch_in==mstr_in[i])
            n++;
    }
    return n;
}

int main()
{

    myString str1;    // Punkt 1.
    str1.Set("Ala ma ");
    myString str2("kota"); //Punkt 2.
    std::cout<<"str1: "<<str1<<std::endl;
    str3=str1+str2;
    std::cout<<"str1+=str2: "<<str3<<std::endl;
    std::cout<<"str1[0]= "<<str3[0]<<std::endl;
    str3[0]='E';
    std::cout<<"==>E: "<<str3<<std::endl;
    myString *str3= new myString("Kasia");
    myString str5;
    str5=*str3;
    str5[0]='B';
    std::cout<<str5<<std::endl;
    int a = count_ch(str5,'a');
    std::cout<<a<<" letters in: "<<str5<<std::endl;
    myString str6;
    std::cin>>str6;
    std::cout<<"str6: "<<str6<<std::endl;

    
    return 0;
}