#include <iostream>
template <class data_type> struct node {
  node *next = nullptr;
  data_type value;
  node(data_type new_value) : value(new_value) {}
  ~node() {
    if (next != nullptr)
      delete next;
  }
};

template <class data_type> class list {
private:
  node<data_type> *head = nullptr;
  size_t size = 0;

public:
  list(data_type new_value) : head(new node<data_type>(new_value)), size(1) {}
  list() {}
  ~list() { delete head; }
};

int main() {
  std::cout << "Hello World!\n";
  return 0;
}
