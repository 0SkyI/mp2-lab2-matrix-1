# Документация к лабораторной работе 1 «Матрицы на шаблонах»

В этой директории хранятся инструкции по выполнению лабораторной работы и
полезные документы.

## Материалы

- Основное описание работы — в корневом [`README.md`](../README.md).
- Курс «Методы программирования 2», ННГУ, кафедра ВМК:
  <https://github.com/UNN-VMK-Software/mp2-lab1-set> (проект-шаблон).
- Документация Google Test: <https://github.com/google/googletest>
- Документация CMake: <https://cmake.org/documentation>

## Структура решения

| Путь | Назначение |
| --- | --- |
| `include/utmatrix.h` | Реализация шаблонных классов `TVector`/`TDynamicVector` и `TMatrix`/`TDynamicMatrix` |
| `test/test_tvector.cpp` | Модульные тесты класса Вектор |
| `test/test_tmatrix.cpp` | Модульные тесты класса Матрица |
| `test/test_main.cpp` | Точка входа приложения с тестами (инициализация Google Test) |
| `samples/sample_matrix.cpp` | Интерактивное тестовое приложение для операций над матрицами |
| `sln/vc9`, `sln/vc10` | Файлы решений и проектов Visual Studio 2008 / 2010 |
| `src/` | Исходные cpp-файлы (в данной работе реализация целиком находится в заголовочном файле, поэтому директория пуста) |

## Сборка и запуск тестов (CMake)

```sh
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j2
ctest --output-on-failure
```
