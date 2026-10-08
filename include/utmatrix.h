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
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0 || sz > static_cast<size_t>(MAX_VECTOR_SIZE))
      throw out_of_range("Vector size should be in range [1, MAX_VECTOR_SIZE]");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && s > 0 && s <= static_cast<size_t>(MAX_VECTOR_SIZE)
           && "TDynamicVector ctor requires non-nullptr arg and valid size");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz])
  {
    std::copy(v.pMem, v.pMem + v.sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
  {
    v.sz = 0;
    v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
      return *this;
    T* tmp = new T[v.sz];
    std::copy(v.pMem, v.pMem + v.sz, tmp);
    delete[] pMem;
    pMem = tmp;
    sz = v.sz;
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v)
      return *this;
    delete[] pMem;
    sz = v.sz;
    pMem = v.pMem;
    v.sz = 0;
    v.pMem = nullptr;
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    assert(ind < sz && "vector index out of range");
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    assert(ind < sz && "vector index out of range");
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= sz)
      throw out_of_range("vector index out of range");
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind >= sz)
      throw out_of_range("vector index out of range");
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    for (size_t i = 0; i < sz; i++)
      if (!(pMem[i] == v.pMem[i]))
        return false;
    return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] + val;
    return res;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] - val;
    return res;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector res(*this);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] * val;
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw length_error("vector sizes mismatch in operator+");
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] + v.pMem[i];
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw length_error("vector sizes mismatch in operator-");
    TDynamicVector res(sz);
    for (size_t i = 0; i < sz; i++)
      res.pMem[i] = pMem[i] - v.pMem[i];
    return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if (sz != v.sz)
      return T();
    T res = pMem[0] * v.pMem[0];
    for (size_t i = 1; i < sz; i++)
      res += pMem[i] * v.pMem[i];
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица -
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz > static_cast<size_t>(MAX_MATRIX_SIZE))
      throw out_of_range("Matrix size should be not greater than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    return this->TDynamicVector<TDynamicVector<T>>::operator==(m);
  }
  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
    return !(*this == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res.pMem[i][j] = pMem[i][j] * val;
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
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
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
      throw length_error("matrix sizes mismatch in operator+");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (sz != m.sz)
      throw length_error("matrix sizes mismatch in operator-");
    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++)
      for (size_t j = 0; j < sz; j++)
        res.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
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
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << endl; // требуется оператор<< для типа T
    return ostr;
  }
};

#endif
