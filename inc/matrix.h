#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <unordered_map>

namespace otus {

  template <typename T, T default_val>
  class Vector {
    class Pool {
    public:
      void assign(size_t index, T value) {
        if (value != default_val) {
          data[index] = value;
        } else {
          if (data.count(index)) data.erase(index);
        }
      }

      T get(size_t index) {
        if (data.count(index)) return data[index];
        else return default_val;
      }

      size_t size() { return data.size(); }

    private:
      std::unordered_map<size_t, T> data { };
    };

    class Proxy {
    public:
      Proxy(size_t index, Pool &pool): index(index), pool(pool) { }

      ~Proxy() = default;
      Proxy(Proxy const &other) = delete;
      Proxy* operator =(Proxy const &other) = delete;
      Proxy(Proxy &&other) = delete;
      Proxy* operator =(Proxy &&other) = delete;

      Proxy* operator =(T const &value) {
        pool.assign(index, value);
        return this;
      }

      operator T() { return pool.get(index); }

    private:
      size_t index;
      Pool &pool;
    };

  public:
    Vector() { }
    size_t size() { return pool.size(); }
    Proxy operator [](size_t index) { return Proxy(index, pool); }

  private:
    Pool pool;
  };

  template <typename T, T default_val>
  class Matrix {
  public:
    Matrix() {}

    size_t size() { return vector.size(); }

    Vector<T, default_val>& operator [](size_t index) { }

  private:
    Vector<T, default_val> vector;
  };
}

#endif
