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

};


int main()
{

}