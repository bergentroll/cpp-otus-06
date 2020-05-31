#include <iostream>

#include "matrix.h"

void pretty_print(otus::Matrix<int, 0> &m) {
  for (int i { 1 }; i < 9; ++i) {
    for (int j { 1 }; j < 9; ++j) {
      std::cout << m[i][j] << ' ';
    }
    std::cout << std::endl;
  }
}

int main() {
  otus::Matrix<int, 0> m { };

  for (int i { }; i < 10; ++i) {
    m[i][i] = i;
    m[i][9 - i] = 9 - i;
  }

  pretty_print(m);

  std::cout << std::endl << "Occupied cells num: " << m.size() << std::endl;

}
