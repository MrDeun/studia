#include <iostream>
template <class DATATYPE> struct Node {
  DATATYPE _data;
  Node(DATATYPE data) : _data(data) {}
  Node<DATATYPE> *next = nullptr;
};

template <class DATATYPE> struct List {
private:
  Node<DATATYPE> *head = nullptr;
  size_t size = 0;

public:
  List() = default;
  List(DATATYPE data) : head(new Node<DATATYPE>(data)), size(1) {}
  void insert(DATATYPE data) {
    if (head == nullptr) {
      head = new Node<DATATYPE>(data);
    } else {
      Node<DATATYPE> *current_node = head;
      while (current_node->next != nullptr) {
        current_node = current_node->next;
      }
      current_node->next = new Node<DATATYPE>(data);
    }
  }
  void erase(DATATYPE data_in) {
    Node<DATATYPE>* current = head;
    Node<DATATYPE>* prev = nullptr;
  }
};

int main() {
  std::cout << "Hello World!\n";
  return 0;
}
