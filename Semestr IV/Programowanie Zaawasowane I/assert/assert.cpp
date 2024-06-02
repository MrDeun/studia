#include <iostream>
#include <cassert>

int main(){
    int even_num = 3;
    const int const_num = 3;
    assert(even_num % 2 == 0);
    static_assert(const_num % 0 == 1,"Static assertion failure: const_num is not ");
    return 0;
}
