#include <cstddef>
#include <iostream>
#include <xerrc.h>

int** init_graph(size_t matrix_size){
    int** new_graph = new int*[matrix_size];
    for (int i = 0 ;i<matrix_size;i++) {
        new_graph[i] = new int[matrix_size];
        for (int j=0 ; j < matrix_size; j++) {
            new_graph[i][j] = 0;
        }
    }
}

int main(){
    size_t test_cases;
    std::cin >> test_cases;
    for (size_t i = 0;i<test_cases;++i) {
        size_t matrix_size, road_count;
        std::cin >> matrix_size >> road_count;
        int** graph = init_graph(matrix_size);
        for (size_t j = 0 ; j < road_count; j++) {
            size_t from, to;
            int weight;
            std::cin >> from >> to >> weight;
            graph[from][to] = weight;
            graph[to][from] = weight;
        }
    }
    return 0;
}