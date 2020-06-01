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
      using IteratorType = typename std::map<IndexType, T>::iterator;

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

      IteratorType begin() { return data.begin(); }

      IteratorType end() { return data.end(); }

    private:
      std::map<IndexType, T> data { };
    };

    // TODO Make indeces compile-time args.
    // TODO Const version.
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

      ProxyCol& operator =(T const &value) {
        pool.assign(index, value);
        return *this;
      }

      operator T() { return pool.get(index); }

      bool operator ==(T const &other) const {
        return pool.get(index) == other;
      }

      bool operator !=(T const &other) const {
        return !(*this == other);
      }

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

    class Iterator {
      public:
      Iterator(typename Pool::IteratorType iterator): iterator(iterator) { }

      std::tuple<std::size_t, std::size_t, T> operator *() {
        return std::tuple_cat(iterator->first, std::make_tuple(iterator->second));
      }

     Iterator operator ++() {
       return Iterator(++iterator);
     }

     bool operator !=(Iterator const &other) {
       return (iterator != other.iterator);
     }

      private:
        typename Pool::IteratorType iterator;
    };

  public:
    Matrix() { }

    std::size_t size() { return pool.size(); }

    ProxyRow operator [](std::size_t index) { return ProxyRow(index, pool); }

    Iterator begin() {
      return Iterator(pool.begin());
    }

    Iterator end() {
      return Iterator(pool.end());
    }

  private:
    Pool pool;
  };
}

#endif
