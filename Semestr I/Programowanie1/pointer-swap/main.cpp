#include <iostream>

void swap(int *pointer) {
  std::cout << "Changing pointer's address...\n";
  int temp = *pointer;

  *pointer = *(pointer + 1);
  *(pointer + 1) = temp;

  return;
}

void print_array(int *array) {
  std::cout << "contents of array: " << *array << " " << *(array + 1);
  return;
}

int main() {
  int array[2] = {3, 11};
  int *array_pointer = array;

  print_array(array_pointer);
  swap(array_pointer);
  print_array(array_pointer);

  return -1;
}
