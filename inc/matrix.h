#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <tuple>
#include <map>

namespace otus {

  template <typename T, T default_val>
  class Matrix {
    class Pool {
    public:
      using IndexType = std::tuple<std::size_t, std::size_t>;
      void assign(IndexType index, T value) {
        if (value != default_val) {
          data[index] = value;
        } else {
          if (data.count(index)) data.erase(index);
        }
      }

      T get(IndexType index) {
        if (data.count(index)) return data[index];
        else return default_val;
      }

      std::size_t size() { return data.size(); }

    private:
      std::map<IndexType, T> data { };
    };

    // TODO Make indeces compile-time args.
    class ProxyCol {
    public:
      ProxyCol(std::size_t row, std::size_t col, Pool &pool):
      index(std::make_tuple(row, col)),
      pool(pool) { }

      ~ProxyCol() = default;
      ProxyCol(ProxyCol const &other) = delete;
      ProxyCol* operator =(ProxyCol const &other) = delete;
      ProxyCol(ProxyCol &&other) = delete;
      ProxyCol* operator =(ProxyCol &&other) = delete;

      ProxyCol* operator =(T const &value) {
        pool.assign(index, value);
        return this;
      }

      operator T() { return pool.get(index); }

    private:
      std::tuple<std::size_t, std::size_t> index;
      Pool &pool;
    };

    class ProxyRow {
    public:
      ProxyRow(std::size_t row, Pool &pool): row(row), pool(pool) { }

      ~ProxyRow() = default;
      ProxyRow(ProxyRow const &other) = delete;
      ProxyRow* operator =(ProxyRow const &other) = delete;
      ProxyRow(ProxyRow &&other) = delete;
      ProxyRow* operator =(ProxyRow &&other) = delete;

      ProxyCol operator [](std::size_t index) {
        return ProxyCol(row, index, pool);
      }

    private:
      std::size_t row;
      Pool &pool;
    };

  public:
    Matrix() { }
    std::size_t size() { return pool.size(); }
    ProxyRow operator [](std::size_t index) { return ProxyRow(index, pool); }

  private:
    Pool pool;
  };
}

#endif
