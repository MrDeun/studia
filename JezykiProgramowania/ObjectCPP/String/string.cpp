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
        size=strlen("chars_in");
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

mystring& myString::operator+(myString& mystr_in)
{
    myString *mystr_tmp=myString[chars];
    *mystr_tmp+=mystr_in;
    return(*mystr_tmp);
}

int main()
{

}