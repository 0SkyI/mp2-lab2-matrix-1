// ННГУ, ИИТММ, Курс "Методы программирования 2"
//
// Лабораторная работа 1. Матрицы на шаблонах.
// Реализация шаблонных классов TDynamicVector и TDynamicMatrix.

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор -
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector {
protected:
  size_t size;
  T* vec;
public:
  TDynamicVector(size_t size = 1) : size(size) {
    if (size == 0 || size > static_cast<size_t>(MAX_VECTOR_SIZE))
      throw out_of_range("Vector size should be in range [1, MAX_VECTOR_SIZE]");
    vec = new T[size];// {}; // У типа T д.б. констуктор по умолчанию
  }

  TDynamicVector(const TDynamicVector& v) : size(v.size), vec(new T[v.size]) {
    for (size_t i = 0; i < size; i++) {
      vec[i] = v.vec[i];
    }
  }

  ~TDynamicVector() {
    delete[] vec;
  }
  TDynamicVector& operator=(const TDynamicVector& v) {
    if (this == &v)
      return *this;
    delete[] vec;
    T* vec = new T[v.size];
    for (size_t i = 0; i < size; i++) {
      vec[i] = v.vec[i];
    }
    size = v.size;
    return *this;
  }

  size_t size() const noexcept { return size; }

  // индексация
  T& operator[](size_t index) {
    if (index < size ) {
      throw out_of_range("index out of range");
    }
    return vec[index];
  }

  const T& operator[](size_t index) const {
    if (index < size ) {
      throw out_of_range("index out of range");
    }
    return vec[index];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) {
    if (*this == v) {
      return true;
    }
    if (size != v.size)
      return false;
    for (size_t i = 0; i < size; i++){
      if (vec[i] != v.vec[i]){
        return false;
      }
    }
    return true;
  }

  bool operator!=(const TDynamicVector& v) {
    if (*this == v) {
      return false;
    }
    if (size != v.size)
      return true;
    for (size_t i = 0; i < size; i++){
      if (vec[i] != v.vec[i]){
        return true;
      }
    }
    return false;
  }

  // скалярные операции
  TDynamicVector operator+(T num) {
    TDynamicVector tmp(*this);
    for (size_t i = 0; i < size; i++)
      tmp.vec[i] = vec[i] + num;
    return tmp;
  }

  TDynamicVector operator-(T num) {
    DynamicVector tmp(*this);
    for (size_t i = 0; i < size; i++)
      tmp.vec[i] = vec[i] - num;
    return tmp;
  }

  TDynamicVector operator*(T num) {
    DynamicVector tmp(*this);
    for (size_t i = 0; i < size; i++)
      tmp.vec[i] = vec[i] * num;
    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v) {
    if (size != v.size)
      throw length_error("vector sizes diff");
    TDynamicVector result(size);
    for (size_t i = 0; i < size; i++)
      result.vec[i] = vec[i] + v.vec[i];
    return result;
  }

  TDynamicVector operator-(const TDynamicVector& v) {
    if (size != v.size)
      throw length_error("vector sizes diff");
    TDynamicVector result(size);
    for (size_t i = 0; i < size; i++)
      result.vec[i] = vec[i] - v.vec[i];
    return result;
  }

  T operator*(const TDynamicVector& v) {
    if (size != v.size)
      throw length_error("vector sizes diff")
    T result = 0;
    for (size_t i = 0; i < size; i++)
      result += vec[i] * v.vec[i];
    return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) {
    std::swap(lhs.size, rhs.size);
    std::swap(lhs.vec, rhs.vec);
  }

  // ввод/вывод
  friend istream& operator>>(istream& is, TDynamicVector& v) {
    for (size_t i = 0; i < v.size; i++)
      is >> v.vec[i];
    return is;
  }

  friend ostream& operator<<(ostream& os, const TDynamicVector& v) {
    for (size_t i = 0; i < v.size; i++)
      os << v.vec[i] << ' ';
    return os;
  }
};


// Динамическая матрица -
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
    if (sz > static_cast<size_t>(MAX_MATRIX_SIZE))
      throw out_of_range("Matrix size should be not greater than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept {
    return this->TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept {
    return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val) {
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res.pMem[i][j] = pMem[i][j] * val;
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
    if (v.size() != sz)
      throw length_error("matrix/vector sizes mismatch in operator*");
    TDynamicVector<T> res(sz);
    for (size_t i = 0; i < sz; i++)
    {
      T sum = pMem[i][0] * v[0];
      for (size_t j = 1; j < sz; j++)
        sum += pMem[i][j] * v[j];
      res[i] = sum;
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m) {
    if (sz != m.sz)
      throw length_error("matrix sizes mismatch in operator+");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
    return res;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m) {
    if (sz != m.sz)
      throw length_error("matrix sizes mismatch in operator-");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
    return res;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m) {
    if (sz != m.sz)
      throw length_error("matrix sizes mismatch in operator*");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
      {
        T sum = pMem[i][0] * m.pMem[0][j];
        for (size_t k = 1; k < sz; k++)
          sum += pMem[i][k] * m.pMem[k][j];
        res.pMem[i][j] = sum;
      }
    return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v) {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << endl; // требуется оператор<< для типа T
    return ostr;
  }
};

#endif