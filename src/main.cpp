#include <iostream>

#include "matrix.h"

int main() {
  otus::Matrix<int, -1> m { };
  std::cout << m.size() << std::endl;
  m[100][100] = 108;
  std::cout << m.size() << std::endl;
  std::cout << m[0][0] << std::endl;
  std::cout << m[100][100] << std::endl;
}
