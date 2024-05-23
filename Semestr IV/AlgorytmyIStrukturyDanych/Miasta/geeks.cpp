#include <cstddef>
#include <iostream>
#include <cstdint>

class DSU {
    size_t* parent;
    size_t* rank;
public:
    DSU(size_t size){
        parent = new size_t[size]; 
        rank = new size_t[size];
        for (int i = 0 ; i < size ; i++) {
            parent[i] = -1;
            rank[i] = 1;
        } 
    }

    size_t find(int i){
        if (parent[i] == -1){
            return 1;
        }
        return parent[i] = find(parent[i]);
    }

};

int main(){
    std::cout << "hello world" << std::endl;
    return 0;
}