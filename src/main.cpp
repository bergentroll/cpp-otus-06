#include <iostream>
#include <cassert>

#include "matrix.h"

void fill(otus::Matrix<int, 0> &m) {
  for (int i { }; i < 10; ++i) {
    m[i][i] = i;
    m[i][9 - i] = 9 - i;
  }
}

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

  fill(m);
  pretty_print(m);

  std::cout << std::endl << "Occupied cells num: " << m.size() << std::endl;

  std::cout << std::endl;
  for(auto [row, col, val]: m) {
    std::cout << "m[" << row << ':' << col << "] = " << val << std::endl;
  }

  ((m[100][100] = 314) = 0) = 217;
  assert(m[100][100] == 217);
}
