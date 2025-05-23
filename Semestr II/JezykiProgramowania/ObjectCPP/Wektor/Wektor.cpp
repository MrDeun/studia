
//Oznaczenia 
#include<stdio.h>
#include<fstream>
#include<iostream>


using namespace std;

struct Vector
{
    int nVal;                       // Oznaczenie ilosci wspolrzednych
    float* Val;                     // Oznaczenie tablicy wspolrzednych
};

void Create(Vector* vec_in, int nVal_in)           //Metoda = Funkcja
{
    vec_in->nVal = nVal_in;
    vec_in->Val = new float[nVal_in];
}

void Destroy(Vector* vec_in)           //Metoda = Funkcja
{
    vec_in->nVal = 0;
    delete[] vec_in->Val;
}
void Show(Vector* vec_in)
{
    cout << "(";
    for (int i = 0; i < (vec_in->nVal); i++)
    {
        cout << vec_in->Val[i];
        if (i != vec_in->nVal - 1)
            cout << ", ";

    }
    cout << ")\n";
}

void Write1(Vector* vec_in, const char* file_out)
{
    ofstream File(file_out);
    File << vec_in->nVal << endl;
    for (int i = 0; i < vec_in->nVal; i++)
    {
        File << vec_in->Val[i] << " ";
    }
    cout << endl;
    File.close();
}

Vector* ReadIn1(const char* file_in)
{
    ifstream File(file_in);
    int n;
    File >> n;
    Vector* temp = new Vector;
    Create(temp, n);
    for (int i = 0; i < n; i++)
    {
        File >> temp->Val[i];
    }
    File.close();
    return temp;
}

// void Write2(Vector* vec_in, const char* file_out)
// {
//     FILE* File = fopen(file_out, "w");
//     fprintf(File, "%i\n", vec_in->nVal);
//     for (int i = 0; i < vec_in->nVal; i++)
//     {
//         if (i != vec_in->nVal - 1)
//             fprintf(File, "%f ", vec_in->Val[i]);
//         else
//             fprintf(File, "%f\n", vec_in->Val[i]);
//     }
//     fclose(File);

// }

// Vector* ReadIn2(const char* file_in)
// {
//     FILE* File = fopen(file_in, "r");
//     int nVal_in;
//     fscanf(File, "%i\n", &nVal_in);
//     Vector* temp = new Vector;
//     Create(temp, nVal_in);
//     for (int i = 0; i < nVal_in; i++)
//         fscanf(File, "%f", &temp->Val[i]);
//     fclose(File);
//     return temp;

// }

int main(const char* filevec1)
{
    Vector v1; Vector v2;
    const int n1 = 5; const int n2 = 10;
    Create(&v1, n1); Create(&v2, n2);
    for (int i = 0; i < n1; i++) v1.Val[i] = (2 * i + 1);
    for (int i = 0; i < n2; i++) v2.Val[i] = (2 * i);
    Show(&v1); 
    Write1(&v1, filevec1); 
    Destroy(&v1);
    Show(&v1);
    Vector* w1 = ReadIn1(filevec1);
    Show(w1); 
    Destroy(w1); 
    Show(w1);
    delete w1; 
    return 0;
}