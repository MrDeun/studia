#include <iostream>

__declspec(dllexport) void say_hello(){
    std::cout << "Hello, from DllExample!\n";
}
