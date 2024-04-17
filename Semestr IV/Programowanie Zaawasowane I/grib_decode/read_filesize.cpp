#include <stdio.h>
#include <iostream>

using namespace std;
///=====================================================================
class Util {
   public:
       static int LengthOfFile(const char* fname);
};
int Util::LengthOfFile(const char* fname)
{
    int res=0;
    FILE* ptr_file = fopen(fname, "rb");
    if (ptr_file==NULL) perror ("Error opening file");
    else {
       fseek(ptr_file, 0, SEEK_END);
       res = ftell(ptr_file);
    }
    fclose(ptr_file);
    return res;
}

///=====================================================================
int main()
{
    char fName[256];
    cout<<"File name:  ";
    cin >> fName;
int Size = Util::LengthOfFile(fName);
    cout << "size of "<<fName<<"  file = "<<Size << endl;

/*
    FILE* pf = fopen(fName, "rb");
 if (pf==NULL) perror ("Error opening file");
 else {
    fseek(pf, 0, SEEK_END);
    int Size = ftell(pf);
    cout << "size of "<<fName<<"  file = "<<Size << endl;
 }
*/
    return 0;
}
///=====================================================================
