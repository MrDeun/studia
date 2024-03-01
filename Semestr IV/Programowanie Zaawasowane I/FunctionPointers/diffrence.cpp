#include <iostream>

#define PI 3.1415
double square(double x)
{
    return x*x;
}

double cubed(double x)
{
    return x*x*x;
}

double line(double x)
{
    return x;
}

double diffrentiate(double(*ptr_func)(double),double x_0, double delta_x)
{
    double numerator = ptr_func(x_0 + delta_x) - ptr_func(x_0);
    return numerator / delta_x;
}

void test_function(double(*ptrfunc)(double),double* test_subject, int test_size)
{
    double x_0 = 1.0;

    for (int i = 0; i < test_size; i++)
    {
        std::cout << "f'(" << test_subject[i] << "x) = " << diffrentiate(ptrfunc,x_0,test_subject[i]) << std::endl;
    }
}

int main()
{
    double test_subject[] = {1.0,0.1,1.0e-5,1.0e-10,1.0e-15,1.0e-17};
    const int test_size = 6;    
    test_function(square,test_subject,test_size);
    std::cout << "\n";
    test_function(cubed,test_subject,test_size);
    std::cout << "\n";
    test_function(line,test_subject,test_size);

    return 0;
}