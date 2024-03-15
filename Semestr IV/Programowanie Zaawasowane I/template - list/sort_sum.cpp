#include <iostream>
#include <cstddef>
template <class T> T sum(T first, T second) { 
    return first + second;
}
template <class T>
T sort(T *Array, size_t ArrayLength) {
    int Comparision=0;
    bool Repeat=false;
    int MaxLength=ArrayLength-1;
    do
    {
        Repeat=false;
        for(int i=0;i<MaxLength;i++)
        {
            if(Array[i]>Array[i+1])
            {
                Repeat=true;
                std::swap(Array[i],Array[i+1]);
            }
            Comparision++;   
        }
        MaxLength=MaxLength-1;
    }while(Repeat==true);
    return Comparision;    
}
int main() { 
    int array[] = {6,1,8,3,-1,12};
    int first = 5, second = 6;
    std::cout << "Sum of ints: " << sum<int>(first,second) << std::endl;
    sort<int>(array,6);

    for (size_t i = 0; i < 6; i++)
    {
        std::cout << " " << array[i];
    }
    

    return 0;
}
