// ННГУ, ИИТММ, Курс "Методы программирования 2"
//
// Лабораторная работа 1. Тестовое приложение для работы с матрицами.
// Позволяет задавать матрицы и осуществлять основные операции над ними.

#include <iostream>
#include <string>
#include "utmatrix.h"
//---------------------------------------------------------------------------
using namespace std;

// Считывает квадратную матрицу размера n с клавиатуры
template<typename T>
TDynamicMatrix<T> ReadMatrix(size_t n)
{
  TDynamicMatrix<T> m(n);
  cout << "Введите " << n * n << " элементов матрицы (по строкам):" << endl;
  cin >> m;
  return m;
}

int main()
{
  setlocale(LC_ALL, "Russian");

  int choice = 0;
  while (choice != 8)
  {
    cout << "\n===== Тестовое приложение: матрицы =====" << endl;
    cout << "1. Сложение матриц (A + B)" << endl;
    cout << "2. Вычитание матриц (A - B)" << endl;
    cout << "3. Умножение матриц (A * B)" << endl;
    cout << "4. Умножение матрицы на число (A * k)" << endl;
    cout << "5. Умножение матрицы на вектор (A * v)" << endl;
    cout << "6. Сравнение матриц (A == B)" << endl;
    cout << "7. Копирование матрицы (B = A)" << endl;
    cout << "8. Выход" << endl;
    cout << "Выберите операцию: ";
    if (!(cin >> choice))
    {
      cout << "Некорректный ввод. Завершение." << endl;
      break;
    }
    if (choice == 8)
      break;

    try
    {
      size_t n = 0;
      cout << "Размер матрицы (n x n), n <= " << MAX_MATRIX_SIZE << ": ";
      cin >> n;
      if (n == 0 || n > static_cast<size_t>(MAX_MATRIX_SIZE))
      {
        cout << "Недопустимый размер матрицы!" << endl;
        continue;
      }

      cout << "Матрица A:" << endl;
      TDynamicMatrix<int> a = ReadMatrix<int>(n);

      if (choice >= 1 && choice <= 3 || choice == 6 || choice == 7)
      {
        cout << "Матрица B:" << endl;
        TDynamicMatrix<int> b = ReadMatrix<int>(n);

        switch (choice)
        {
        case 1:
          cout << "A + B =" << endl << (a + b);
          break;
        case 2:
          cout << "A - B =" << endl << (a - b);
          break;
        case 3:
          cout << "A * B =" << endl << (a * b);
          break;
        case 6:
          cout << "A == B ? " << (a == b ? "ДА" : "НЕТ") << endl;
          break;
        case 7:
          b = a;
          cout << "Копия B после присваивания B = A:" << endl << b;
          break;
        }
      }
      else if (choice == 4)
      {
        int k = 0;
        cout << "Множитель k: ";
        cin >> k;
        cout << "A * " << k << " =" << endl << (a * k);
      }
      else if (choice == 5)
      {
        TDynamicVector<int> v(n);
        cout << "Вектор v (" << n << " элементов):" << endl;
        cin >> v;
        cout << "A * v = " << (a * v) << endl;
      }
      else
      {
        cout << "Неизвестная операция." << endl;
      }
    }
    catch (const exception& ex)
    {
      cout << "Ошибка: " << ex.what() << endl;
    }
  }

  return 0;
}
//---------------------------------------------------------------------------
