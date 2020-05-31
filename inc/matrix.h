#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <unordered_map>

namespace otus {
  template <typename T, T default_val>
  class Vector {
  public:
    Vector() { }
    size_t size() { }
    T& operator[](size_t index) { }
  private:
    std::unordered_map<size_t, T> data { };
  };

  template <typename T, T default_val>
  class Matrix {
  public:
    Matrix() {}
    size_t size() {}
    Vector<T, default_val>& operator[](size_t index) {}
  private:
  };
}

#endif
