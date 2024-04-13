#include <cstdarg>
#include <iostream>
void my_print(const char *args_types, ...) {
  va_list arguments;
  va_start(arguments, args_types);
  while (*args_types != '\0') {
    if (*args_types == 'c') {
      int i = va_arg(arguments, int);
      std::cout << static_cast<char>(i) << '\n';
    } else if (*args_types == 'i') {
      int i = va_arg(arguments,int);
      std::cout << i << '\n';
    } else {
      std::cerr << "my_print broke!";
    }
    ++args_types;
  }
  va_end(arguments);
}

int main(int argc, char *argv[]) {
  my_print("cci", 'H','l', 63);
  return 0;
}
