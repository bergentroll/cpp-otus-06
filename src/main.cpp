#include <iostream>

#include "matrix.h"

int main() {
  otus::Vector<int, -1> v { };
  std::cout << v.size() << std::endl;
  v[100] = 108;
  std::cout << v.size() << std::endl;
  std::cout << v[0] << std::endl;
  std::cout << v[100] << std::endl;
}
