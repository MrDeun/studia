#include<fstream>
#include<iostream>


class Vector
{
    private:
        int VectorCount;
        float *VectorValue;
    public:
        Vector(int VectorCount_in)
        {
            VectorCount = VectorCount_in;
            VectorValue = new float[VectorCount_in];
        }
        ~Vector()
        {
            VectorCount = 0;
            delete[] VectorValue;
        }
        void Show();
        void WriteToFile(const char *File_Name);
        void ReadFromFile(const char *File_Name);
        bool Set(int VectorCount_in, float VectorValue_in)
        {
            if(VectorCount_in>=0&&VectorCount_in<VectorCount)
            {
                VectorValue[VectorCount_in]=VectorValue_in;
                return true;
            }
                return false;
        }
        float Get(int VectorCount_in)
        {
                return VectorValue[VectorCount_in];
        }
        
};

void Vector::Show()
{
        std::cout << "(";
    for (int i = 0; i < VectorCount; i++)
    {
        std::cout << VectorValue[i];
        if (i != VectorCount - 1)
            std::cout << ", ";

    }
    std::cout << ")\n";
}

void Vector::WriteToFile(const char* File_Name)
{
    std::ofstream File(File_Name);
    File << VectorCount << std::endl;
    for (int i = 0; i < VectorCount; i++)
        File << VectorValue[i] << " ";
    std::cout << std::endl;
    File.close();
}

void Vector::ReadFromFile(const char* File_Name)
{
    std::ifstream File(File_Name);
    if(VectorValue)
        delete[] VectorValue;
    File>>VectorCount;
    VectorValue=new float[VectorCount];
        for (int i = 0; i < VectorCount; i++)
    {
        File >> VectorValue[i];
    }
    File.close();
}
int main()
{
    Vector Vector1(5);
}