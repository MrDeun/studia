#include <iostream>

void print_array(int* array, int array_size){
    for (int i = 0; i < array_size; i++){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    return;
}

void swap(int& value_1, int& value_2){
    int temp = value_1;
    value_1 = value_2;
    value_2 = temp;
    return;
}

int* fill_array(int array_size){
    int* new_array = new int[array_size];
    for (int i = 0; i < array_size; i++){
        int temp;
        std::cin >> temp;
        new_array[i] = temp;
    }
    return new_array;
}

void heapify(int* array, int array_size, int index){
    int largest = index;
    int left = 2*index+1;
    int right = 2*index+2;
    if(left < array_size && array[left] > array[largest]){
        largest = left;
    }
    if(right < array_size && array[right] > array[largest]){
        largest = right;
    }
    if (largest != index){
        swap(array[index],array[largest]);
        heapify(array,array_size,largest);
    }
    
}

void arrange_heap(int* array, int size){
    for (int i = size / 2 - 1; i >= 0 ; i--){
        heapify(array,size,i);
    }
    return;
}

void heap_sort(int* array, int size){
    arrange_heap(array,size);
    for (int i = size - 1; i >= 0; i--){
        swap(array[i],array[0]);
        heapify(array,i,0);
        if (i > 1) {
            print_array(array,i);
        }
    }
    
}

int main(){
    size_t cases{};
    std::cin >> cases;
    for (size_t i = 0; i < cases; i++) {
        int array_size{};
        std::cin >> array_size;
        int* array = fill_array(array_size);
        print_array(array,array_size);
        heap_sort(array,array_size);
        print_array(array,array_size);
        std::cout << '\n';
        delete[] array;
    }
        
    
    return 0;
}